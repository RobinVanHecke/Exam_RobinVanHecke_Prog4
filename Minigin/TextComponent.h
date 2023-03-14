#pragma once
#include <memory>
#include <string>

#include "Component.h"

namespace dae
{
	class Font;
	class Texture2D;
}


class TextComponent final : public Component
{
public:
	explicit TextComponent(dae::GameObject* gameObject);

	void SetText(const std::string& text);
	void SetFont(const std::shared_ptr<dae::Font>& pFont);

	void Update(float /*deltaT*/) override;


private:
	bool m_NeedsUpdate{ false };

	std::string m_Text;
	std::shared_ptr<dae::Font> m_pFont;

};

