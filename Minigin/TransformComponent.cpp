#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
}

void TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
