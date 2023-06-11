#include "ButtonComponent.h"

#include "GameObject.h"
#include "InputManager.h"
#include "TransformComponent.h"

ButtonComponent::ButtonComponent(dae::GameObject* pOwner)
	: Component(pOwner), m_Pos(), m_Width(0), m_Height(0)
{
}

void ButtonComponent::Setup(const glm::vec2& pos, const float width, const float height, const std::function<void()>& onClick)
{
	m_Pos = pos;
	m_Width = width;
	m_Height = height;
	m_OnClick = onClick;

	dae::InputManager::GetInstance().AddButton(this);
	GetOwner()->GetComponent<TransformComponent>()->SetLocalPosition(pos);
}

void ButtonComponent::OnMouseClick(const glm::vec2& mousePos) const
{
	if (mousePos.x > m_Pos.x && mousePos.x < m_Pos.x + m_Width &&
		mousePos.y > m_Pos.y && mousePos.y < m_Pos.y + m_Height)
		m_OnClick();
}