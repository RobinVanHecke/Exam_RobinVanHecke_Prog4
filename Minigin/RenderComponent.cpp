#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

RenderComponent::RenderComponent(dae::GameObject* gameObject) :
	Component(gameObject)
{
	if (GetOwner()->GetComponent<TextureComponent>() != nullptr)
	{
		m_pTexture = GetOwner()->GetComponent<TextureComponent>();
	}

	if (GetOwner()->GetComponent<TransformComponent>() != nullptr)
	{
		m_pTransform = GetOwner()->GetComponent<TransformComponent>();
	}
}

void RenderComponent::Render() const
{
	if (m_pTexture != nullptr)
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture->GetTexture(), m_pTransform->GetWorldPosition().x, m_pTransform->GetWorldPosition().y);
}
