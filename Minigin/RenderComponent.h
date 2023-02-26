#pragma once
#include "ComponentBase.h"
#include "Renderer.h"

class RenderComponent final: public ComponentBase
{
public:
	template<typename T> void Render(T texture, T transform);
private:
};

template <typename T>
void RenderComponent::Render(T texture, T transform)
{
	if (texture != nullptr)
	{
		const auto& pos = transform.GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
	}
}

