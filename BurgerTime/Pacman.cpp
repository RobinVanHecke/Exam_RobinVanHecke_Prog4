#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include "GameObject.h"

#include "TextComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "ButtonComponent.h"
#include "SoundCommand.h"

#include "InputManager.h"
#include "SoundSystem.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("MainMenu");
	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	// In Engine
	constexpr float windowWidth = 416.f;

	// SOUND
	auto pSoundSystem = new dae::SoundSystem();
	pSoundSystem->AddSound("../Data/Sounds/01_Start.wav");
	auto soundCommand = std::make_unique<SoundCommand>(pSoundSystem);
	dae::InputManager::GetInstance().AddCommand(std::move(soundCommand), dae::KeyState::Pressed, dae::InputManager::Key::P);

	// BACKGROUND
	//const auto goBackground = std::make_shared<dae::GameObject>();
	//goBackground->AddComponent<TextureComponent>()->SetTexture("../Data/Textures/Level1.png");
	//goBackground->AddComponent<RenderComponent>();
	//scene.Add(goBackground);

	// LOGO
	const auto goLogo = std::make_shared<dae::GameObject>();
	goLogo->AddComponent<TextureComponent>()->SetTexture("../Data/Textures/Logo.png");
	const auto logoSize = goLogo->GetComponent<TextureComponent>()->GetSize();
	goLogo->GetComponent<TransformComponent>()->SetLocalPosition(windowWidth / 2.f - static_cast<float>(logoSize.x) / 2.f, 0.f);
	goLogo->AddComponent<RenderComponent>();
	scene.Add(goLogo);

	// BUTTONS
	// SINGLE
	const auto goSingle = std::make_shared<dae::GameObject>();
	goSingle->AddComponent<TextureComponent>();
	goSingle->AddComponent<TextComponent>()->SetText("Single Player");
	goSingle->GetComponent<TextComponent>()->SetFont(font);
	goSingle->GetComponent<TextComponent>()->MakeTexture();
	auto SingleClick = [&]
	{
		dae::InputManager::GetInstance().RemoveButtons();

		//TODO LEVEL MANAGER
	};
	const auto singleSize = goSingle->GetComponent<TextComponent>()->GetSize();
	const glm::vec2 singlePos{ windowWidth / 2.f - static_cast<float>(singleSize.x) / 2.f, 150.f };
	goSingle->AddComponent<ButtonComponent>()->Setup(singlePos,static_cast<float>(singleSize.x), static_cast<float>(singleSize.y), SingleClick);
	goSingle->GetComponent<TransformComponent>()->SetLocalPosition(singlePos.x, singlePos.y);
	goSingle->AddComponent<RenderComponent>();
	scene.Add(goSingle);

	// COOP
	const auto goCoop = std::make_shared<dae::GameObject>();
	goCoop->AddComponent<TextureComponent>();
	goCoop->AddComponent<TextComponent>()->SetText("CO-OP");
	goCoop->GetComponent<TextComponent>()->SetFont(font);
	goCoop->GetComponent<TextComponent>()->MakeTexture();
	auto coopClick = [&]
	{
		dae::InputManager::GetInstance().RemoveButtons();

		//TODO LEVEL MANAGER
	};
	const auto coopSize = goCoop->GetComponent<TextComponent>()->GetSize();
	const glm::vec2 coopPos{ windowWidth / 2.f - static_cast<float>(coopSize.x) / 2.f, 250.f };
	goCoop->AddComponent<ButtonComponent>()->Setup(singlePos, static_cast<float>(coopSize.x), static_cast<float>(coopSize.y), coopClick);
	goCoop->GetComponent<TransformComponent>()->SetLocalPosition(coopPos.x, coopPos.y);
	goCoop->AddComponent<RenderComponent>();
	scene.Add(goCoop);

	// VERSUS
	const auto goVersus = std::make_shared<dae::GameObject>();
	goVersus->AddComponent<TextureComponent>();
	goVersus->AddComponent<TextComponent>()->SetText("Versus");
	goVersus->GetComponent<TextComponent>()->SetFont(font);
	goCoop->GetComponent<TextComponent>()->MakeTexture();
	auto versusClick = [&]
	{
		dae::InputManager::GetInstance().RemoveButtons();

		//TODO LEVEL MANAGER
	};
	const auto versusSize = goCoop->GetComponent<TextComponent>()->GetSize();
	const glm::vec2 versusPos{ windowWidth / 2.f - static_cast<float>(versusSize.x) / 2.f, 350.f };
	goVersus->AddComponent<ButtonComponent>()->Setup(singlePos, static_cast<float>(versusSize.x), static_cast<float>(versusSize.y), versusClick);
	goVersus->GetComponent<TransformComponent>()->SetLocalPosition(versusPos.x, versusPos.y);
	goVersus->AddComponent<RenderComponent>();
	scene.Add(goVersus);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}