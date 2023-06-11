#include "SoundCommand.h"

SoundCommand::SoundCommand(dae::BaseSoundSystem* pSoundSystem) : m_pSoundSystem(pSoundSystem)
{
	dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<dae::BaseSoundSystem>(pSoundSystem));

}

void SoundCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem().PlaySound(0u, 25);
}