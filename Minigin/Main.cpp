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

	const auto goBackground = std::make_shared<dae::GameObject>();
	goBackground->AddComponent<TextureComponent>()->SetTexture("background.tga");
	goBackground->AddComponent<RenderComponent>();
	scene.Add(goBackground);

	const auto goLogo = std::make_shared<dae::GameObject>();
	goLogo->AddComponent<TextureComponent>()->SetTexture("logo.tga");
	goLogo->AddComponent<TransformComponent>()->SetPos(216.f, 180.f);
	goLogo->AddComponent<RenderComponent>();
	scene.Add(goLogo);

	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto goTitle = std::make_shared<dae::GameObject>();
	goTitle->AddComponent<TextComponent>()->SetText("Programming 4 Assignment");
	goTitle->GetComponent<TextComponent>()->SetFont(font);
	goTitle->AddComponent<TransformComponent>()->SetPos(80.f, 50.f);
	goTitle->AddComponent<TextureComponent>();
	goTitle->AddComponent<RenderComponent>();
	scene.Add(goTitle);

	const auto goFps = std::make_shared<dae::GameObject>();
	goFps->AddComponent<FpsComponent>();
	goFps->AddComponent<TextComponent>()->SetText(goFps->GetComponent<FpsComponent>()->GetFps());
	goFps->GetComponent<TextComponent>()->SetFont(font);
	goFps->AddComponent<TransformComponent>()->SetPos(0.f, 0.f);
	goFps->AddComponent<TextureComponent>();
	goFps->AddComponent<RenderComponent>();
	scene.Add(goFps);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}