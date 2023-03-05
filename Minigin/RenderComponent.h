#pragma once
#include <memory>
#include <glm/vec3.hpp>

#include "ComponentBase.h"


namespace dae
{
	class Texture2D;
}

class TransformComponent;
class TextureComponent;

class RenderComponent final : public ComponentBase
{
public:
	RenderComponent(dae::GameObject* gameObject);

	void Render() const override;
private:
	std::shared_ptr<TextureComponent> m_pTexture{ nullptr };
	std::shared_ptr<dae::Texture2D> m_pTexture2D{ nullptr };


	std::shared_ptr <TransformComponent> m_pTransform{ nullptr };
	glm::vec3 m_Position{ 0.f,0.f,0.f };
};
