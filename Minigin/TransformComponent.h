#pragma once
#include <glm/vec3.hpp>

#include "Component.h"

class TransformComponent final : public Component
{
public:
	explicit TransformComponent(dae::GameObject* gameObject);

	void SetPosition(glm::vec3 newPos);
	void SetPosition(float newX, float newY, float newZ = 0.f);
	glm::vec3 GetPosition() const { return m_Position; }

	void SetRotation(glm::vec3 newRotation);
	void SetRotation(float newX, float newY, float newZ = 0.f);
	glm::vec3 GetRotation() const { return m_Rotation; }

	void SetScale(glm::vec3 newScale);
	void SetScale(float newX, float newY, float newZ = 0.f);
	glm::vec3 GetScale() const { return m_Scale; }

private:
	glm::vec3 m_Position{};
	glm::vec3 m_Rotation{};
	glm::vec3 m_Scale{};
};