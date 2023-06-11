#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>

#include "Component.h"
#include "EventListener.h"
#include "EventQueue.h"

class HealthComponent final : public Component, public dae::EventListener
{
public:
	explicit HealthComponent(dae::GameObject* gameObject) : Component(gameObject){}
	~HealthComponent() override { dae::EventQueue::GetInstance().RemoveListener(this); }

	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) = delete;

	void OnEvent(std::any data, int id, bool engineEvent) override;

	void SetValues(int lives, bool player = true);
	void SetValues(int lives, bool player = true, const glm::vec2& UIpos, const std::string& texturePath);

	void Update(float deltaT) override;
	void Damage(int lives, bool castEvent = true);
	void Reset();
	void ShowUI(glm::vec2 UIpos, const std::string& texturePath);

	void Die() { m_CurrentLives = 0; }
	int GetLives() const { return m_CurrentLives; }

	float GetTimeDeath() const { return m_TimeDeath; }

	void SetTimeStunned(const float time) { m_TimeStunned = time; }
	float GetTimeStunned() const { return m_TimeStunned; }

	void SetEnemyCollision(const bool colliding) { m_EnemyCollision = colliding; }
	bool GetEnemyCollision() const { return m_EnemyCollision; }

private:
	int m_OriginalLives{}, m_CurrentLives{};

	float m_TimeDeath{}, m_TimeLife{}, m_TimeStunned{};

	bool m_Player{};
	bool m_EnemyCollision{};

	std::vector<dae::GameObject*> m_pUIobjects;
};

