#pragma once
#include <memory>

#include "ComponentBase.h"

namespace dae
{
	class Texture2D;
}

class TextureComponent final : public ComponentBase
{
public:
	void SetTexture(const std::shared_ptr<dae::Texture2D>& texture);
	std::shared_ptr<dae::Texture2D> GetTexture() const { return m_Texture; }
	
private:
	std::shared_ptr<dae::Texture2D> m_Texture;
};
