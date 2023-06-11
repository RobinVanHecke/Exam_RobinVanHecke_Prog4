#pragma once
#include <string>

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
		static void RegisterSoundSystem(BaseSoundSystem* pSoundSystem) { m_pSoundSystem = pSoundSystem; }

	private:
		static BaseSoundSystem* m_pSoundSystem;
	};
}
