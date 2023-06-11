#pragma once
#include <glm/vec2.hpp>

#include "Command.h"

namespace dae
{
	class ThumbCommand: public Command
	{
	public:
		ThumbCommand() = default;
		~ThumbCommand() override = default;

		void Execute() override = 0;
		void SetDirection(const glm::vec2& direction) { m_Direction = direction; }

	protected:
		glm::vec2 m_Direction{};
	};
}
