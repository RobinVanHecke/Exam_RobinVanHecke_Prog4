#pragma once
#include "ComponentBase.h"

class RenderComponent final: public ComponentBase
{
public:
	RenderComponent();
	~RenderComponent();
	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;

	void Update() override;
};

