#pragma once
#include "ComponentBase.h"


class TransformComponent;
class TextureComponent;

class RenderComponent final : public ComponentBase
{
public:
	RenderComponent(const std::shared_ptr<dae::GameObject>& gameObject);

	void Render() const override;
private:
	TextureComponent* m_pTexture{ nullptr };
	TransformComponent* m_pTransform{ nullptr };
};
