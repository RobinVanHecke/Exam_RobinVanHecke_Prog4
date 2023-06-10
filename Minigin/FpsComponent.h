#pragma once
#include "Component.h"

class FpsComponent final : public Component
{
public:
	FpsComponent(dae::GameObject* gameObject);

	void Update(float deltaT) override;
};
