#pragma once
#include <glm/vec2.hpp>

#include "Component.h"

class TransformComponent final : public Component
{
public:
	explicit TransformComponent(dae::GameObject* gameObject);
	~TransformComponent() = default;

#pragma region world
	void SetWorldPosition(const glm::vec2& newPos) { SetWorldPosition(newPos.x, newPos.y); }
	void SetWorldPosition(float newXPos, float newYPos);
	const glm::vec2& GetWorldPosition();

	void SetWorldRotation(float newRotation, bool degrees = true);
	float GetWorldRotation(bool degrees = true);

	void SetWorldScale(const glm::vec2& newScale) { SetWorldScale(newScale.x, newScale.y); }
	void SetWorldScale(float newXScale, float newYScale);
	glm::vec2 GetWorldScale();
#pragma endregion

#pragma region local
	void SetLocalPosition(const glm::vec2& newPos) { SetLocalPosition(newPos.x, newPos.y); }
	void SetLocalPosition(float newXPos, float newYPos);
	glm::vec2 GetLocalPos() const { return m_LocalPosition; }

	void SetLocalRotation(float newRotation, bool degrees = true);
	float GetLocalRotation(bool degrees = true) const;

	void SetLocalScale(const glm::vec2& newScale) { SetLocalScale(newScale.x, newScale.y); }
	void SetLocalScale(float newXScale, float newYScale);
	glm::vec2 GetLocalScale() const { return m_LocalScale; }
#pragma endregion

	bool IsDirty() const { return m_DirtyFlag; }
	void SetDirty();

	void Translate(const glm::vec2& xy) { Translate(xy.x, xy.y); }
	void Translate(float x, float y);

	void Rotate(float angle, bool degrees);

private:
	void UpdateTransform();

	glm::vec2 m_WorldPosition{};
	float m_WorldRotation{};
	glm::vec2 m_WorldScale{};

	glm::vec2 m_LocalPosition{};
	float m_LocalRotation{};
	glm::vec2 m_LocalScale{};

	bool m_DirtyFlag{};
};