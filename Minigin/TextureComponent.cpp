#include "TextureComponent.h"
#include "Texture2D.h"

void TextureComponent::SetTexture(const std::shared_ptr<dae::Texture2D>& texture)
{
	m_Texture = texture;
}
