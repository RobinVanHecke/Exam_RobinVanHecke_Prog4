#pragma once
#include "ComponentBase.h"

class TextComponent final: public ComponentBase
{
public:
	TextComponent();
	~TextComponent();
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	void Update() override;
};

