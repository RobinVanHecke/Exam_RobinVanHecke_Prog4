#include "SoundCommand.h"

SoundCommand::SoundCommand(dae::BaseSoundSystem* pSoundSystem) : m_pSoundSystem(pSoundSystem)
{
	dae::ServiceLocator::RegisterSoundSystem(std::move(m_pSoundSystem));
}

void SoundCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem().PlaySound(0u, 25);
}