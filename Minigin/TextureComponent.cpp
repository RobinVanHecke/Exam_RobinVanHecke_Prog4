#include "TextureComponent.h"

#include <SDL.h>

SDL_Texture* TextureComponent::GetSDLTexture() const
{
	return m_texture;
}

TextureComponent::TextureComponent(SDL_Texture* texture)
{
	m_texture = texture;
}

TextureComponent::~TextureComponent()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 TextureComponent::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}
