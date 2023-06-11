#include "ButtonComponent.h"

#include "GameObject.h"
#include "InputManager.h"
#include "TransformComponent.h"

namespace dae
{
	ButtonComponent::ButtonComponent(GameObject* pOwner, const glm::vec2& pos, float width, float height, std::function<void()> onClick)
		: Component(pOwner), m_Pos{ pos }, m_Width{ width }, m_Height{ height }, m_OnClick{ onClick }
	{
		InputManager::GetInstance().AddButton(this);

		pOwner->GetComponent<TransformComponent>()->SetLocalPosition(pos);
	}

	void ButtonComponent::OnMouseClick(const glm::vec2& mousePos) const
	{
		if (mousePos.x > m_Pos.x && mousePos.x < m_Pos.x + m_Width &&
			mousePos.y > m_Pos.y && mousePos.y < m_Pos.y + m_Height)
			m_OnClick();
	}


}
