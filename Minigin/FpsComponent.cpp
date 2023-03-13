#include "FpsComponent.h"

#include "GameObject.h"
#include "TextComponent.h"

class TextComponent;

FpsComponent::FpsComponent(dae::GameObject* gameObject):
ComponentBase(gameObject)
{
}

void FpsComponent::Update(const float deltaT)
{
	m_Fps = 1 / deltaT;

	m_Fps = floor(m_Fps);

	m_FpsString = std::to_string(static_cast<int>(m_Fps));
	GetOwner()->GetComponent<TextComponent>()->SetText(m_FpsString);
}
