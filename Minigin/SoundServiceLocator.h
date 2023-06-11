#pragma once
#include <string>
#include <memory>

namespace  dae
{
	class BaseSoundSystem
	{
	public:
		virtual ~BaseSoundSystem() = default;
		virtual void AddSound(const std::string& filePath) = 0;
		virtual void PlaySound(unsigned short id, const int volume) = 0;
	};

	class DefaultSoundSystem final : public BaseSoundSystem
	{
	public:
		void AddSound(const std::string& /*filepath*/) override{}
		void PlaySound(unsigned short, const int) override {}
	};

	class ServiceLocator final
	{
	public:
		static BaseSoundSystem& GetSoundSystem() { return *m_pSoundSystem; }
		static void RegisterSoundSystem(std::unique_ptr<BaseSoundSystem> pSoundSystem) { m_pSoundSystem = std::move(pSoundSystem); }

	private:
		static std::unique_ptr<BaseSoundSystem> m_pSoundSystem;
	};
}
