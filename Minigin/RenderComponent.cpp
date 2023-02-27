#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

RenderComponent::RenderComponent(const std::shared_ptr<dae::GameObject>& gameObject) :
	ComponentBase(gameObject)
{
	m_pTexture = GetOwner()->GetComponent<TextureComponent>();
	m_pTransform = GetOwner()->GetComponent<TransformComponent>();
}

void RenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto& pos = m_pTransform->GetPos();
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture->GetTexture(), pos.x, pos.y);
	}
}
