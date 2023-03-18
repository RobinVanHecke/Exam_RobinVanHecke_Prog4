#include "TransformComponent.h"

TransformComponent::TransformComponent(dae::GameObject* gameObject) :
	Component(gameObject)
{
}

void TransformComponent::SetPosition(const glm::vec3 newPos)
{
	m_Position = newPos;
}

void TransformComponent::SetPosition(const float newX, const float newY, const float newZ)
{
	m_Position.x = newX;
	m_Position.y = newY;
	m_Position.z = newZ;
}

void TransformComponent::SetRotation(glm::vec3 newRotation)
{
	m_Rotation = newRotation;
}

void TransformComponent::SetRotation(float newX, float newY, float newZ)
{
	m_Rotation.x = newX;
	m_Rotation.y = newY;
	m_Rotation.z = newZ;
}

void TransformComponent::SetScale(glm::vec3 newScale)
{
	m_Scale = newScale;
}

void TransformComponent::SetScale(float newX, float newY, float newZ)
{
	m_Scale.x = newX;
	m_Scale.y = newY;
	m_Scale.z = newZ;
}