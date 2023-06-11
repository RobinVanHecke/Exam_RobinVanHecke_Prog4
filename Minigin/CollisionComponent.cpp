#include "CollisionComponent.h"

#include "CollisionManager.h"
#include "TransformComponent.h"

CollisionComponent::~CollisionComponent()
{
	dae::CollisionManager::GetInstance().RemoveCollider(this);
}

void CollisionComponent::SetValues(const float width, const float height)
{
	m_Width = width;
	m_Height = height;

	dae::CollisionManager::GetInstance().AddCollider(this);
}