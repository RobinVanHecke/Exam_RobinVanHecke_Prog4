#include "GameObject.h"

#include "TransformComponent.h"

void dae::GameObject::Update(const float deltaT)
{
	// Update components
	for (auto& pComponent : m_pComponents)
		pComponent.second->Update(deltaT);

	// TODO Update Children
//	for (auto& pChild : m_pChildren)
//		pChild->Update(deltaT);
	
}

void dae::GameObject::Render() const
{
	// Render components
	for (const auto& pComponent: m_pComponents)
		pComponent.second->Render();

	// TODO Render Children
//	for (auto& pChild : m_pChildren)
//		pChild->Render();
}

void dae::GameObject::SetDeleted(const bool deleted)
{
	m_Deleted = deleted;
}

bool dae::GameObject::GetDeleted() const
{
	return m_Deleted;
}

dae::GameObject::GameObject()
{
	// GameObject always has a Transform Component
	AddComponent<TransformComponent>()->SetPosition(0.f,0.f);
}

dae::GameObject::~GameObject()
{
	for (const auto& pChild : m_pChildren)
		delete pChild;
}

void dae::GameObject::SetParent(GameObject* pNewParent)
{
	// if new parent is same as current parent
	if (m_pParent == pNewParent) 
		return;

	// remove from children 
	if (m_pParent)
		m_pParent->RemoveChild(this);

	// set new parent
	m_pParent = pNewParent;

	// add to new parents children
	if (m_pParent)
		m_pParent->AddChild(this);

	if (const auto transform = GetComponent<TransformComponent>())
	{
		const auto oldPosition = transform->GetPosition();
		const auto oldRotation = transform->GetRotation();
		const auto oldScale = transform->GetScale();

		if (m_pParent)
		{
			if (const auto parentTransform = m_pParent->GetComponent<TransformComponent>())
			{
				transform->SetPosition(oldPosition + parentTransform->GetPosition());
				transform->SetRotation(oldRotation + parentTransform->GetRotation());
				transform->SetScale(oldScale + parentTransform->GetScale());
			}
		}

		else
		{
			transform->SetPosition(oldPosition);
			transform->SetRotation(oldRotation);
			transform->SetScale(oldScale);
		}
	}
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.push_back(pChild);
}

void dae::GameObject::RemoveChild(const GameObject* pChild)
{
	if (const auto it = std::find(m_pChildren.begin(), m_pChildren.end(), pChild); 
		it != m_pChildren.end())
	{
		m_pChildren.erase(it);
	}
}
