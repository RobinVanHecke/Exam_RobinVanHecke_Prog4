#pragma once
#include "ComponentBase.h"

class RenderComponent final: public ComponentBase
{
public:
	RenderComponent(const std::shared_ptr<dae::GameObject>& gameObject);

	void Render();
private:
};
