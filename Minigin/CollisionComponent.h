#pragma once
#include <glm/vec2.hpp>

#include "Component.h"
#include "GameObject.h"

class CollisionComponent final : public Component
{
public:
	CollisionComponent(dae::GameObject* pOwner): Component(pOwner), m_pCollisionOwner(pOwner){}
	~CollisionComponent() override;

	void SetValues(float width, float height);

	float GetWidth() const { return m_Width; }
	float GetHeight() const { return m_Height; }

	dae::GameObject* GetCollisionOwner() const { return m_pCollisionOwner; }

private:
	float m_Width{}, m_Height{};

	dae::GameObject* m_pCollisionOwner{};
};
