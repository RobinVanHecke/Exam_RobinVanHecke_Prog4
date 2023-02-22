#pragma once
#include "ComponentBase.h"

class TransformComponent final: public ComponentBase
{
	void Update() override;

	TransformComponent();
	~TransformComponent();
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;
};

