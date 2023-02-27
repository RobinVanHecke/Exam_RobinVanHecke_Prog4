#pragma once
#include <glm/vec3.hpp>

#include "ComponentBase.h"

class TransformComponent final : public ComponentBase
{
public:
	TransformComponent(const std::shared_ptr<dae::GameObject>& gameObject);

	void SetPos(glm::vec3 newPos);
	void SetPos(float newX, float newY, float newZ);
	glm::vec3 GetPos() const;

private:
	glm::vec3 m_Position{};
};