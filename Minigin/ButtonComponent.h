#pragma once
#include <glm/vec2.hpp>
#include <functional>

#include "Component.h"

class ButtonComponent final : public Component
{
public:
	ButtonComponent(dae::GameObject* pOwner);

	void Setup(const glm::vec2& pos, float width, float height, const std::function<void()>& onClick);

	void OnMouseClick(const glm::vec2& mousePos) const;

private:
	glm::vec2 m_Pos;

	float m_Width, m_Height;

	std::function<void()> m_OnClick;
};