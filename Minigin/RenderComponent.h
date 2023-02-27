#pragma once
#include "ComponentBase.h"
#include "Renderer.h"
#include "Transform.h"

class RenderComponent final: public ComponentBase
{
public:
	template<typename T> void Render(T texture, dae::Transform position);
private:
};

template <typename T>
void RenderComponent::Render(T texture, dae::Transform position)
{
	if (texture != nullptr)
	{
		const auto& pos = position.GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
	}
}

