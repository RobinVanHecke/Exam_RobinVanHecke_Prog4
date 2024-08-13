#pragma once
#include <memory>
#include "Command.h"
#include "SoundServiceLocator.h"


class SoundCommand final : public dae::Command
{
public:
	SoundCommand(dae::BaseSoundSystem* pSoundSystem);
	~SoundCommand() override = default;

	void Execute() override;

private:
	std::unique_ptr<dae::BaseSoundSystem> m_pSoundSystem;
};