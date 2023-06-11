#pragma once
#include <memory>

#include "SoundServiceLocator.h"

namespace dae
{
	class SoundSystem final : public BaseSoundSystem
	{
	public:
		SoundSystem();

		void AddSound(const std::string& filePath) override;
		void PlaySound(const unsigned short id, const int volume) override;

	private:
		class SoundSystemImpl;
		std::unique_ptr<SoundSystemImpl> m_pSoundSystemImpl;
	};
}