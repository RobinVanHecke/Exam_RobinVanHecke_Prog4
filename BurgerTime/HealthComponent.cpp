#include "HealthComponent.h"

#include "EngineEvents.h"
#include "Events.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

void HealthComponent::OnEvent(std::any data, int id, const bool engineEvent)
{
	if (!engineEvent || m_CurrentLives <= 0)
		return;

	if (id == static_cast<int>(dae::EngineEvents::CollisionEvent))
	{
		
	}
}

void HealthComponent::SetValues(const int lives, const bool player)
{
	m_OriginalLives = lives;
	m_CurrentLives = lives;

	m_Player = player;

	dae::EventQueue::GetInstance().AddListener(this);
}

void HealthComponent::SetValues(const int lives, const glm::vec2& UIpos, const std::string& texturePath, const bool player)
{
	SetValues(lives, player);

	ShowUI(UIpos, texturePath);
}

void HealthComponent::Update(const float deltaT)
{
	if (m_CurrentLives <= 0)
		m_TimeDeath += deltaT;
	else
		m_TimeLife += deltaT;
}

void HealthComponent::Damage(const int lives, const bool castEvent)
{
	if (m_CurrentLives > 0 && m_TimeLife > 1.f)
	{
		m_TimeLife = .0f;

		m_CurrentLives -= lives;

		if (m_Player && castEvent)
			dae::EventQueue::GetInstance().AddEvent(std::any(), static_cast<int>(Event::LostLife), false);

		if (m_CurrentLives <= 0)
		{
			m_TimeDeath = .0f;

			if (castEvent)
			{
				if (m_Player)
					dae::EventQueue::GetInstance().AddEvent(std::any(), static_cast<int>(Event::PlayerDeath), false);
				else
					dae::EventQueue::GetInstance().AddEvent(std::any(GetOwner()->GetComponent<TextureComponent>()), static_cast<int>(Event::EnemyDeath), false);
			}
		}
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