#pragma once
#include <memory>
#include <string>

#include "ComponentBase.h"

namespace dae
{
	class Font;
	class Texture2D;
}

class TextComponent final : public ComponentBase
{
public:
	TextComponent() = default;
	TextComponent(const std::string& text, std::shared_ptr<dae::Font> font);

	void SetText(const std::string& text);
	std::shared_ptr<dae::Texture2D> GetTextTexture() const { return m_TextTexture; }

	void Update();


private:
	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<dae::Font> m_Font;
	std::shared_ptr<dae::Texture2D> m_TextTexture;
};

