#include "GameObject.h"


dae::GameObject::~GameObject()
{
	m_Components.erase(m_Components.begin(), m_Components.end());
	m_Components.clear();
}

void dae::GameObject::Update(const float deltaT)
{
	for (const auto& component : m_Components)
	{
		component.second->Update(deltaT);
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_Components)
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

void dae::GameObject::SetParent(GameObject* pNewParent)
{
	m_pParent->RemoveChild(this);

	m_pParent = pNewParent;

	pNewParent->AddChild();

	// TODO update position rotation and scale
}


void dae::GameObject::AddChild()
{
	m_pChildren.push_back(this);
}

void dae::GameObject::RemoveChild(GameObject* /*pChild*/)
{
	// TODO make remove child
}
