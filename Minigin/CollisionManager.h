#pragma once
#include "CollisionComponent.h"
#include "EventQueue.h"
#include "Singleton.h"

namespace dae
{
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void Update();
		void AddCollider(CollisionComponent* pComponent) { m_pComponents.push_back(pComponent); }
		void RemoveCollider(const CollisionComponent* pComponent);

	private:
		std::vector<CollisionComponent*> m_pComponents;
		EventQueue* m_pEventQueue = nullptr;

		bool Colliding(const glm::vec2& firstPos, float firstWidth, float firstHeight, const glm::vec2& secondPos, float secondWidth, float secondHeight);
	};

	struct CollidedObjects
	{
		CollidedObjects() = default;

		CollidedObjects(GameObject* pObject, GameObject* pOtherObject) : m_pObject(pObject), m_pOtherObject(pOtherObject)
		{}

		GameObject * m_pObject{ nullptr };
		GameObject * m_pOtherObject{ nullptr };
	};
}
