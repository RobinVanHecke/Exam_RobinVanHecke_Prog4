#pragma once
#include <memory>
#include <string>

#include "ComponentBase.h"

namespace dae
{
	class Texture2D;
}

class TextureComponent final : public ComponentBase
{
public:
	TextureComponent(dae::GameObject* gameObject);
	
	void SetTexture(const std::shared_ptr<dae::Texture2D>& texture);
	void SetTexture(const std::string& filename);
	std::shared_ptr<dae::Texture2D> GetTexture() const { return m_pTexture; }
	
private:
	std::shared_ptr<dae::Texture2D> m_pTexture;
};
