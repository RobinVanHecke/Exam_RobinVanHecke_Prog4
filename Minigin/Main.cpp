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

	//auto go = std::make_shared<dae::GameObject>();
	//go->SetTexture("background.tga");
	//scene.Add(go);

	//go = std::make_shared<dae::GameObject>();
	//go->SetTexture("logo.tga");
	//go->SetPosition(216, 180);
	//scene.Add(go);

	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);



	// todo test
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto test = std::make_shared<dae::GameObject>();

	test->AddComponent<TextComponent>();
	test->AddComponent<TransformComponent>();
	test->AddComponent<TextureComponent>();
	test->AddComponent<RenderComponent>();

	test->GetComponent<TextComponent>()->SetFont(font);
	test->GetComponent<TextComponent>()->SetText("Programming 4 Assignment");

	test->GetComponent<TransformComponent>()->SetPos(80.f, 0.f, 0.f);

	scene.Add(test);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}