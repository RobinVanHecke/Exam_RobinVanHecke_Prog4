#include "TextComponent.h"

#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include <stdexcept>

#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Texture2D.h"
class TextureComponent;

TextComponent::TextComponent(dae::GameObject* gameObject):
Component(gameObject)
{
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetFont(const std::shared_ptr<dae::Font>& pFont)
{
	m_pFont = pFont;
}

void TextComponent::Update(float /*deltaT*/)
{
	if (m_NeedsUpdate)
	{
		constexpr SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);

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

		if (!m_Text.empty())
		{
			GetOwner()->GetComponent<TextureComponent>()->SetTexture(std::make_unique<dae::Texture2D>(texture));
			m_Size = GetOwner()->GetComponent<TextureComponent>()->GetSize();
		}

		m_NeedsUpdate = false;
	}
}

glm::ivec2 TextComponent::GetSize()
{
	return m_Size;
}
