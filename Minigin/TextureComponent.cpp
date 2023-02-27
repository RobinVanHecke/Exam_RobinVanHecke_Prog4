#include "TextureComponent.h"
#include "Texture2D.h"

TextureComponent::TextureComponent(const std::shared_ptr<dae::GameObject>& gameObject) :
	ComponentBase(gameObject)
{
}

void TextureComponent::SetTexture(const std::shared_ptr<dae::Texture2D>& texture)
{
	m_Texture = texture;
}
