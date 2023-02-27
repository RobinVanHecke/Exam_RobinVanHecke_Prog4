#include "ComponentBase.h"

#include "GameObject.h"

void ComponentBase::Update()
{
}

ComponentBase::ComponentBase(std::shared_ptr<dae::GameObject> gameObject):
m_pOwner(std::move(gameObject))
{
}
