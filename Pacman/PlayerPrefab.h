#pragma once
#include <memory>
#include <string>
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
	class Scene;
}

class PlayerPrefab final
{
public:
	PlayerPrefab(dae::Scene* pScene, const std::string& texturePath, const glm::vec2& pos, const glm::vec2& UIpos, const std::string& UItexturePath, int lives = 3, bool keyboard = true, float moveSpeed = 100);

	~PlayerPrefab() = default;
	PlayerPrefab(const PlayerPrefab&) = delete;
	PlayerPrefab(PlayerPrefab&&) = delete;
	PlayerPrefab& operator=(const PlayerPrefab&) = delete;
	PlayerPrefab& operator=(PlayerPrefab&&) = delete;

	std::shared_ptr<dae::GameObject> GetGameObject() { return std::move(m_pObject); }

private:
	std::shared_ptr<dae::GameObject> m_pObject;
};

