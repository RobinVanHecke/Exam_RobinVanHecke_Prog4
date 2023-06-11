#include "SoundServiceLocator.h"

namespace dae
{
	BaseSoundSystem* ServiceLocator::m_pSoundSystem{ new DefaultSoundSystem };
}