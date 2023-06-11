#include "HealthComponent.h"

#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

void HealthComponent::SetValues(const int lives, const bool player)
{
	m_OriginalLives = lives;
	m_CurrentLives = lives;

	m_Player = player;

	dae::EventQueue::GetInstance().AddListener(this);
}

void HealthComponent::SetValues(const int lives, const bool player, const glm::vec2& UIpos, const std::string& texturePath)
{
	m_OriginalLives = lives;
	m_CurrentLives = lives;

	m_Player = player;

	dae::EventQueue::GetInstance().AddListener(this);

	ShowUI(UIpos, texturePath);
}

void HealthComponent::Update(const float deltaT)
{
	if (m_CurrentLives <= 0)
		m_TimeDeath += deltaT;
	else
		m_TimeLife += deltaT;
}

void HealthComponent::Damage(int lives, bool castEvent)
{
	if (m_CurrentLives > 0 && m_TimeLife > 1.f)
	{
		m_TimeLife = .0f;

		m_CurrentLives -= lives;
	}
}

void HealthComponent::Reset()
{
	m_CurrentLives = m_OriginalLives;
	m_TimeDeath = .0f;
}

void HealthComponent::ShowUI(const glm::vec2 UIpos, const std::string& texturePath)
{
	if (!m_pUIobjects.empty())
		return;

	dae::Scene* pScene{ dae::SceneManager::GetInstance().GetScene(0) };

	if (!pScene)
		return;

	constexpr float offset{ 20 };

	for (int i = 0; i < m_CurrentLives; ++i)
	{
		auto goLife = std::make_shared<dae::GameObject>();
		goLife->AddComponent<TextureComponent>()->SetTexture(texturePath);
		goLife->GetComponent<TransformComponent>()->SetLocalPosition(UIpos.x + static_cast<float>(i) * offset, UIpos.y);
		pScene->Add(goLife);

		m_pUIobjects.push_back(goLife.get());
	}
}
