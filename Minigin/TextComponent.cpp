#include "TextComponent.h"

#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include <stdexcept>

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"


TextComponent::TextComponent(const std::string& text, std::shared_ptr<dae::Font> font)
	: m_NeedsUpdate(true), m_Text(text), m_Font(std::move(font)), m_TextTexture(nullptr)
{ }

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<dae::Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}