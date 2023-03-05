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
	m_Fps = deltaT;

	GetOwner()->GetComponent<TextComponent>()->SetText(deltaT);
}
