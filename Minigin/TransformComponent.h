#pragma once
#include <glm/vec3.hpp>

#include "ComponentBase.h"

class TransformComponent final: public ComponentBase
{
public:
	TransformComponent();
	~TransformComponent();
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

	void Update() override;

	const glm::vec3& GetPosition() const { return m_Position; }
	void SetPosition(float x, float y, float z);

private:
	glm::vec3 m_Position;
};

