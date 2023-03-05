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
#include "TextObject.h"
#include "Scene.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextureComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	const auto go1 = std::make_shared<dae::GameObject>();
	go1->AddComponent<TextureComponent>()->SetTexture("background.tga");
	go1->AddComponent<RenderComponent>();
	scene.Add(go1);

	const auto go2 = std::make_shared<dae::GameObject>();
	go2->AddComponent<TextureComponent>()->SetTexture("logo.tga");
	go2->AddComponent<TransformComponent>()->SetPos(216.f, 180.f);
	go2->AddComponent<RenderComponent>();
	scene.Add(go2);

	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto to = std::make_shared<dae::GameObject>();

	to->AddComponent<TextComponent>();
	to->AddComponent<TransformComponent>();
	to->AddComponent<TextureComponent>();
	to->AddComponent<RenderComponent>();

	to->GetComponent<TextComponent>()->SetFont(font);
	to->GetComponent<TextComponent>()->SetText("Programming 4 Assignment");

	to->GetComponent<TransformComponent>()->SetPos(80.f, 0.f);

	scene.Add(to);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}