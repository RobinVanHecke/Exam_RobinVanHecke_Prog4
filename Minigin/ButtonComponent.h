#pragma once
#include <glm/vec2.hpp>
#include <functional>

#include "Component.h"

namespace dae
{
	class ButtonComponent final : public Component
	{
	public:
		ButtonComponent(GameObject* pOwner, const glm::vec2& pos, float width, float height, std::function<void()> onClick);

		void OnMouseClick(const glm::vec2& mousePos) const;

	private:
		glm::vec2 m_Pos;

		float m_Width, m_Height;

		std::function<void()> m_OnClick;
	};


}
