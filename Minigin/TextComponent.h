#pragma once
#include "ComponentBase.h"

class TextComponent final: public ComponentBase
{
	void Update() override;

	TextComponent();
	~TextComponent();
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;
};

