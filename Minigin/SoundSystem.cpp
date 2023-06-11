#include "SoundSystem.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>


namespace dae
{
	class SoundSystem::SoundSystemImpl final
	{
	public:
		SoundSystemImpl()
		{
			if (SDL_Init(SDL_INIT_AUDIO) == -1)
				std::cout << "failed to init audio: " << SDL_GetError() << '\n';

			if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
				std::cout << "failed to open audio device: " << Mix_GetError() << '\n';

			m_Thread = std::jthread{ [&] { SoundThread(); } };
		}

		~SoundSystemImpl()
		{
			for (const auto& pSound : m_pSounds)
				Mix_FreeChunk(pSound);

			m_Continue = false;
			m_Condition.notify_all();

			Mix_CloseAudio();
		}

		void SoundThread()
		{
			while (m_Continue)
			{
				std::unique_lock lock(m_Mutex);
				m_Condition.wait(lock);

				if (!m_Queue.empty() && m_Continue)
				{
					const auto& [id, volume]{ m_Queue.front() };
					m_Queue.pop();

					lock.unlock();
					PlaySound(id, volume);
				}
			}
		}

		void AddSound(const std::string& filePath)
		{
			if (Mix_Chunk* pMixChunk{ Mix_LoadWAV(filePath.c_str()) })
				m_pSounds.push_back(pMixChunk);
		}

		void AddToQueue(const unsigned short id, const int volume)
		{
			const std::lock_guard lock{ m_Mutex };
			m_Queue.push({ id, volume });
			m_Condition.notify_all();
		}

		void PlaySound(const unsigned short id, const int volume) const
		{
			if (static_cast<unsigned long long>(id) > m_pSounds.size())
			{
				std::cout << "invalid id\n";
				return;
			}

			int rightVolume;
			if (volume > MIX_MAX_VOLUME)
				rightVolume = MIX_MAX_VOLUME;
			else if (volume < 0)
				rightVolume = 0;
			else
				rightVolume = volume;

			Mix_Volume(-1, rightVolume);
			Mix_PlayChannel(-1, m_pSounds[id], 0);
		}

	private:
		std::vector<Mix_Chunk*> m_pSounds{};
		std::queue<std::pair<const unsigned short, const int>> m_Queue;

		std::jthread m_Thread{};
		std::mutex m_Mutex{};
		std::condition_variable m_Condition{};
		std::atomic<bool> m_Continue{ true };
	};

	SoundSystem::SoundSystem()
		: m_pSoundSystemImpl{ std::make_unique<SoundSystemImpl>() }
	{}

	void SoundSystem::AddSound(const std::string& filePath)
	{
		m_pSoundSystemImpl->AddSound(filePath);
	}

	void SoundSystem::PlaySound(const unsigned short id, const int volume)
	{
		m_pSoundSystemImpl->AddToQueue(id, volume);
	}
}
