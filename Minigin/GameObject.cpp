#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(const float /*deltaT*/)
{
	
}

void dae::GameObject::Render() const
{
	//const auto& pos = m_Transform.GetPosition();
	
}


void dae::GameObject::SetDeleted(const bool deleted)
{
	m_Deleted = deleted;
}

bool dae::GameObject::GetDeleted() const
{
	return m_Deleted;
}
