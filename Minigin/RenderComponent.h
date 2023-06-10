#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include "Component.h"


namespace dae
{
	class Texture2D;
}

class TransformComponent;
class TextureComponent;

class RenderComponent final : public Component
{
public:
	explicit RenderComponent(dae::GameObject* gameObject);

	void Render() const override;
private:
	TextureComponent* m_pTexture{ nullptr };
	std::shared_ptr<dae::Texture2D> m_pTexture2D{ nullptr };


	TransformComponent* m_pTransform{ nullptr };
	glm::vec2 m_Position{ 0.f,0.f };
};
