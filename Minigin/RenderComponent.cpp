#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"

RenderComponent::RenderComponent(const std::shared_ptr<dae::GameObject>& gameObject) :
	ComponentBase(gameObject)
{
}

void RenderComponent::Render()
{
	if (m_pOwner.get()->GetComponent<TextureComponent>()->GetTexture() != nullptr)
	{
		const auto& pos = m_transform.GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}
