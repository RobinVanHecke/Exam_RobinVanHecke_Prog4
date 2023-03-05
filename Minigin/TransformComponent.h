#pragma once
#include <glm/vec3.hpp>

#include "ComponentBase.h"

class TransformComponent final : public ComponentBase
{
public:
	TransformComponent(dae::GameObject* gameObject);

	void SetPos(glm::vec3 newPos);
	void SetPos(float newX, float newY, float newZ = 0.f);
	glm::vec3 GetPos() const;

private:
	glm::vec3 m_Position{};
};