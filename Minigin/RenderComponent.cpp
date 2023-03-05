#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

RenderComponent::RenderComponent(dae::GameObject* gameObject) :
	ComponentBase(gameObject)
{
	if (GetOwner()->GetComponent<TextureComponent>())
	{
		m_pTexture = std::shared_ptr<TextureComponent>(GetOwner()->GetComponent<TextureComponent>());
		m_pTexture2D = m_pTexture->GetTexture();
	}

	if (GetOwner()->GetComponent<TransformComponent>())
	{
		m_pTransform = std::shared_ptr <TransformComponent>(GetOwner()->GetComponent<TransformComponent>());
		m_Position = m_pTransform->GetPos();
	}
}

void RenderComponent::Render() const
{
	//TODO try to use m_pTexture2D instead of m_pTexture->GetTexture()
	if (m_pTexture != nullptr)
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture->GetTexture(), m_Position.x, m_Position.y);
}
