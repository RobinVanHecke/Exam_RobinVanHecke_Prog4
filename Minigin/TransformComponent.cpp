#include "TransformComponent.h"

#include <glm/detail/func_trigonometric.inl>

#include "GameObject.h"

TransformComponent::TransformComponent(dae::GameObject* gameObject) :
	Component(gameObject)
{
}

#pragma region world
void TransformComponent::SetWorldPosition(const float newXPos, const float newYPos)
{
	const auto pOwnerParent = GetOwner()->GetParent();

	if (!pOwnerParent)
	{
		m_LocalPosition.x = newXPos;
		m_LocalPosition.y = newYPos;
	}

	else
	{
		auto* pOwnParTransform = pOwnerParent->GetComponent<TransformComponent>();

		const auto& ownParPos = pOwnParTransform->GetWorldPosition();
		const auto& ownParScale = pOwnParTransform->GetWorldScale();
		const float ownParRot = pOwnParTransform->GetWorldRotation(false);

		const float cosRot = std::cos(-ownParRot);
		const float sinRot = std::sin(-ownParRot);

		const float moveX = newXPos - ownParPos.x;
		const float moveY = newXPos - ownParPos.y;

		m_LocalPosition.x = (moveX * cosRot - moveY * sinRot) / ownParScale.x;
		m_LocalPosition.y = (moveX * sinRot + moveY * cosRot) / ownParScale.y;
	}

	SetDirty();
}

const glm::vec2& TransformComponent::GetWorldPosition() 
{
	if (m_DirtyFlag)
		UpdateTransform();

	return m_WorldPosition;
}

void TransformComponent::SetWorldRotation(const float newRotation, const bool degrees)
{
	const float worldRot = GetWorldRotation();
	const float newRot = degrees ? glm::radians(newRotation) : newRotation;

	m_LocalRotation += newRot - worldRot;

	SetDirty();
}

float TransformComponent::GetWorldRotation(const bool degrees)
{
	if (m_DirtyFlag)
		UpdateTransform();

	if (degrees)
		return glm::degrees(m_WorldRotation);
	return m_WorldRotation;
}

void TransformComponent::SetWorldScale(const float newXScale, const float newYScale)
{
	const auto& worldScale = GetWorldScale();

	m_LocalScale.x = newXScale / worldScale.x;
	m_LocalScale.y = newYScale / worldScale.y;

	SetDirty();
}

glm::vec2 TransformComponent::GetWorldScale()
{
	if (m_DirtyFlag)
		UpdateTransform();

	return m_WorldScale;
}

#pragma endregion

#pragma region local
void TransformComponent::SetLocalPosition(const float newXPos, const float newYPos)
{
	m_LocalPosition.x = newXPos;
	m_LocalPosition.y = newYPos;

	SetDirty();
}

void TransformComponent::SetLocalRotation(const float newRotation, const bool degrees)
{
	if (degrees)
		m_LocalRotation = glm::radians(newRotation);
	else
		m_LocalRotation = newRotation;

	SetDirty();
}

float TransformComponent::GetLocalRotation(const bool degrees) const
{
	if (degrees)
		return glm::degrees(m_LocalRotation);
	return  m_LocalRotation;
}

void TransformComponent::SetLocalScale(const float newXScale, const float newYScale)
{
	m_LocalScale.x = newXScale;
	m_LocalScale.y = newYScale;

	SetDirty();
}
#pragma endregion

void TransformComponent::SetDirty()
{
	m_DirtyFlag = true;

	const auto pOwner = GetOwner();
	if (!pOwner)
		return;

	for (const auto& pChildren = pOwner->GetChildren(); const auto & pChild : pChildren)
	{
		const auto pTransform = pChild->GetComponent<TransformComponent>();
		if (!pTransform)
			continue;

		pTransform->SetDirty();
	}
}

void TransformComponent::Translate(const float x, const float y)
{
	m_LocalPosition.x += x;
	m_LocalPosition.y += y;

	SetDirty();
}

void TransformComponent::Rotate(const float angle, const bool degrees)
{
	const float currentAngle = degrees ? glm::radians(angle) : angle;

	m_LocalRotation += currentAngle;

	SetDirty();
}

void TransformComponent::UpdateTransform()
{
	m_DirtyFlag = false;

	const auto pOwnerParent = GetOwner()->GetParent();

	if (!pOwnerParent)
	{
		m_WorldPosition = m_LocalPosition;
		m_WorldRotation = m_LocalRotation;
		m_WorldScale = m_LocalScale;
		return;
	}

	const auto pOwnParTransform{ pOwnerParent->GetComponent<TransformComponent>() };
	const glm::vec2& ownParPos{ pOwnParTransform->GetWorldPosition() };
	const float ownParRot{ pOwnParTransform->GetWorldRotation() };
	const glm::vec2& ownParScale{ pOwnParTransform->GetWorldScale() };


	const float cosRot{ cosf(ownParRot) };
	const float sinRot{ sinf(ownParRot) };

	m_WorldPosition.x = ownParPos.x + m_LocalPosition.x * cosRot * ownParScale.x - m_LocalPosition.y * sinRot * ownParScale.y;
	m_WorldPosition.y = ownParPos.y + m_LocalPosition.x * sinRot * ownParScale.x + m_LocalPosition.y * cosRot * ownParScale.y;
	m_WorldRotation = ownParRot + m_LocalRotation;
	m_WorldScale = ownParScale * m_LocalScale;
}
