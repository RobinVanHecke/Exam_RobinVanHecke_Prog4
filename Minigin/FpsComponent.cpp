#include "FpsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

class TextComponent;

FpsComponent::FpsComponent(dae::GameObject* gameObject):
Component(gameObject)
{}

void FpsComponent::Update(const float deltaT)
{
	float fps = 1 / deltaT;
	fps = floor(fps);

	const std::string fpsString = std::to_string(static_cast<int>(fps));
	GetOwner()->GetComponent<TextComponent>()->SetText(fpsString);
}
