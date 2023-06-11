#include "SoundServiceLocator.h"

namespace dae
{
	std::unique_ptr<BaseSoundSystem> ServiceLocator::m_pSoundSystem{ new DefaultSoundSystem };
}