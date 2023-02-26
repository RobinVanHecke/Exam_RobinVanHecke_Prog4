#pragma once

#include <glm/vec3.hpp>

#include "ComponentBase.h"

class TransformComponent final: public ComponentBase
{
public:
	TransformComponent() = default;
	TransformComponent (float x, float y, float z);

	const glm::vec3& GetPosition() const { return m_Position; }
	void SetPosition(float x, float y, float z);

private:
	glm::vec3 m_Position;

};

