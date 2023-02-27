#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(const float /*deltaT*/)
{
	for (const auto component : m_Components)
	{
		component.second->Update();
	}
}

void dae::GameObject::Render() const
{
	for (const auto component : m_Components)
	{
		component.second->Render();
	}
	
}


void dae::GameObject::SetDeleted(const bool deleted)
{
	m_Deleted = deleted;
}

bool dae::GameObject::GetDeleted() const
{
	return m_Deleted;
}
