#include "TextureComponent.h"

#include "ResourceManager.h"
#include "Texture2D.h"

TextureComponent::TextureComponent(dae::GameObject* gameObject) :
	ComponentBase(gameObject)
{
}

void TextureComponent::SetTexture(const std::shared_ptr<dae::Texture2D>& texture)
{
	m_pTexture = texture;
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}
