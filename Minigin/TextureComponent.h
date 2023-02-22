#pragma once
#include <glm/vec2.hpp>

#include "ComponentBase.h"

struct SDL_Texture;

class TextureComponent final : public ComponentBase
{
public:
	SDL_Texture* GetSDLTexture() const;
	explicit TextureComponent(SDL_Texture* texture);
	~TextureComponent() override;

	glm::ivec2 GetSize() const;

	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other) = delete;

	void Update() override;

private:
	SDL_Texture* m_texture;
};

