#include "CollisionManager.h"

#include "EngineEvents.h"
#include "TransformComponent.h"

void dae::CollisionManager::Update()
{
	if (!m_pEventQueue)
		m_pEventQueue = &EventQueue::GetInstance();

	for (const auto & pComponent : m_pComponents)
	{
		auto pos1 = pComponent->GetCollisionOwner()->GetComponent<TransformComponent>()->GetLocalPos();
		const float width1 = pComponent->GetWidth();
		const float height1 = pComponent->GetHeight();

		for (const auto & pOtherComponent : m_pComponents)
		{
			if (pComponent == pOtherComponent)
				continue;

			auto pos2 = pOtherComponent-> GetCollisionOwner()->GetComponent<TransformComponent>()->GetLocalPos();
			const float width2 = pOtherComponent->GetWidth();
			const float height2 = pOtherComponent->GetHeight();

			if (Colliding(pos1, width1, height1, pos2, width2, height2))
				m_pEventQueue->AddEvent(std::any
				(CollidedObjects(pComponent->GetCollisionOwner(), pOtherComponent->GetCollisionOwner())), 
					static_cast<int>(EngineEvents::CollisionEvent), true);
		}
	}
}

void dae::CollisionManager::RemoveCollider(const CollisionComponent* pComponent)
{
	if (!m_pComponents.empty())
		std::erase_if(m_pComponents, [&](const CollisionComponent* pOtherComponent) {return pComponent == pOtherComponent; });
}

bool dae::CollisionManager::Colliding(const glm::vec2& firstPos, const float firstWidth, const float firstHeight,
                                      const glm::vec2& secondPos, const float secondWidth, const float secondHeight)
{
	if (firstPos.x >= secondPos.x + secondWidth || secondPos.x >= firstPos.x + firstWidth)
		return false;

	if (firstPos.y >= secondPos.y + secondHeight || secondPos.y >= firstPos.y + firstHeight)
		return false;

	return true;
}
