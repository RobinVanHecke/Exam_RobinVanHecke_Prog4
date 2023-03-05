#include "TransformComponent.h"

TransformComponent::TransformComponent(dae::GameObject* gameObject) :
	ComponentBase(gameObject)
{
}

void TransformComponent::SetPos(const glm::vec3 newPos)
{
	m_Position = newPos;
}

void TransformComponent::SetPos(const float newX, const float newY, const float newZ)
{
	m_Position.x = newX;
	m_Position.y = newY;
	m_Position.z = newZ;
}

glm::vec3 TransformComponent::GetPos() const
{
	return m_Position;
}
