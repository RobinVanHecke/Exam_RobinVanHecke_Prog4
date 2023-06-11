#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(const float deltaT)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaT);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::OnGUI()
{
	for (const auto & scene : m_scenes)
		scene->OnGUI();
	
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

dae::Scene* dae::SceneManager::GetScene(const int index) const
{
	if (static_cast<int>(m_scenes.size()) <= index)
		return nullptr;

	return m_scenes[index].get();
}