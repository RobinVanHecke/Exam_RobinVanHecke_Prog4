#include "ComponentBase.h"

#include "GameObject.h"


ComponentBase::ComponentBase(dae::GameObject* gameObject):
m_pOwner(gameObject)
{
}
