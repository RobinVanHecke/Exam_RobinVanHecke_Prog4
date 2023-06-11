#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "FpsComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	const auto goBackground = std::make_shared<dae::GameObject>();
	goBackground->AddComponent<TextureComponent>()->SetTexture("background.tga");
	goBackground->AddComponent<RenderComponent>();
	scene.Add(goBackground);

	const auto goLogo = std::make_shared<dae::GameObject>();
	goLogo->AddComponent<TextureComponent>()->SetTexture("logo.tga");
	goLogo->GetComponent<TransformComponent>()->SetWorldPosition(216.f, 180.f);
	goLogo->AddComponent<RenderComponent>();
	scene.Add(goLogo);

	const auto goTitle = std::make_shared<dae::GameObject>();
	goTitle->AddComponent<TextComponent>()->SetText("Programming 4 Assignment");
	goTitle->GetComponent<TextComponent>()->SetFont(font);
	goTitle->GetComponent<TransformComponent>()->SetWorldPosition(80.f, 50.f);
	goTitle->AddComponent<TextureComponent>();
	goTitle->AddComponent<RenderComponent>();
	scene.Add(goTitle);

	const auto goFps = std::make_shared<dae::GameObject>();
	goFps->AddComponent<FpsComponent>();
	goFps->AddComponent<TextComponent>();
	goFps->GetComponent<TextComponent>()->SetFont(font);
	goFps->GetComponent<TransformComponent>()->SetWorldPosition(0.f, 0.f);
	goFps->AddComponent<TextureComponent>();
	goFps->AddComponent<RenderComponent>();
	scene.Add(goFps);

	const auto goChef = std::make_shared<dae::GameObject>();
	goChef->GetComponent<TransformComponent>()->SetWorldPosition(100.f, 300.f);
	goChef->AddComponent<TextureComponent>()->SetTexture("Chef.png");
	goChef->AddComponent<RenderComponent>();
	scene.Add(goChef);

	const auto goHotDog = std::make_shared<dae::GameObject>();
	goHotDog->GetComponent<TransformComponent>()->SetLocalPosition(200.f, 300.f);
	goHotDog->AddComponent<TextureComponent>()->SetTexture("MrHotDog.png");
	goHotDog->AddComponent<RenderComponent>();
	scene.Add(goHotDog);

	const auto goPickle = std::make_shared<dae::GameObject>();
	goPickle->GetComponent<TransformComponent>()->SetLocalPosition(300.f, 300.f);
	goPickle->AddComponent<TextureComponent>()->SetTexture("MrPickle.png");
	goPickle->AddComponent<RenderComponent>();
	scene.Add(goPickle);

	const auto goEgg = std::make_shared<dae::GameObject>();
	goEgg->GetComponent<TransformComponent>()->SetLocalPosition(400.f, 300.f);
	goEgg->AddComponent<TextureComponent>()->SetTexture("MrEgg.png");
	goEgg->AddComponent<RenderComponent>();
	scene.Add(goEgg);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}