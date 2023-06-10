#include "GameObject.h"

#include <ranges>

#include "TransformComponent.h"

void dae::GameObject::Update(const float deltaT)
{
	// Update components
	for (const auto& pCompValue : m_pComponents | std::views::values)
		pCompValue->Update(deltaT);

	for (const auto& pChild : m_pChildren)
		pChild->Update(deltaT);
}

void dae::GameObject::Render() const
{
	// Render components
	for (const auto& pCompValue : m_pComponents | std::views::values)
		pCompValue->Render();

	for (auto& pChild : m_pChildren)
		pChild->Render();
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
	// GameObject always has a Transform Component by default
	AddComponent<TransformComponent>()->SetWorldPosition(0.f,0.f);
}

void dae::GameObject::SetParent(GameObject* pNewParent)
{
	if (const auto pOldParent = m_pParent)
	{
		// if new parent is same as current parent
		if (pOldParent == pNewParent)
			return;

		// remove from children
		pOldParent->RemoveChild(this);
	}

	else
	{
		if (!pNewParent)
			return;

		pNewParent->AddChild(this);
	}

	m_pParent = pNewParent;

	const auto pTransform = GetComponent<TransformComponent>();
	if (!pTransform)
		return;

	if (pNewParent)
	{
		if (const auto pNewParentTransform = pNewParent->GetComponent<TransformComponent>())
			pTransform->SetLocalPosition(pTransform->GetWorldPosition() - pNewParentTransform->GetWorldPosition());
	}
	else
		pTransform->SetLocalPosition(pTransform->GetWorldPosition());

	/*

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
		const auto oldPosition = transform->GetWorldPosition();
		const auto oldRotation = transform->GetWorldRotation();
		const auto oldScale = transform->GetWorldScale();

		if (m_pParent)
		{
			if (const auto parentTransform = m_pParent->GetComponent<TransformComponent>())
			{
				transform->SetWorldPosition(oldPosition + parentTransform->GetWorldPosition());
				transform->SetWorldRotation(oldRotation + parentTransform->GetWorldRotation());
				transform->SetWorldScale(oldScale + parentTransform->GetWorldScale());
			}
		}

		else
		{
			transform->SetWorldPosition(oldPosition);
			transform->SetWorldRotation(oldRotation);
			transform->SetWorldScale(oldScale);
		}
	}
	*/
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.push_back(std::unique_ptr<GameObject>(pChild));
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	auto it = std::ranges::find_if(m_pChildren,[pChild](const std::unique_ptr<GameObject>& c)
		{ return c.get() == pChild; });

	if (it != m_pChildren.end())
	{
		(*it)->m_pParent = nullptr;
		m_pChildren.erase(it);
	}
}
