#include "PlayerPrefab.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "TransformComponent.h"

//PlayerPrefab::PlayerPrefab(dae::Scene* pScene, const std::string& texturePath, const glm::vec2& pos,
//                           const glm::vec2& UIpos, const std::string& UItexturePath, int lives, bool keyboard, float moveSpeed)
//{
//	m_pObject = std::make_shared<dae::GameObject>();
//	m_pObject->GetComponent<TransformComponent>()->SetLocalPosition(pos.x, pos.y);
//
//	m_pObject->AddComponent<RenderComponent>();
//	m_pObject->AddComponent<HealthComponent>();
//
//
//	pScene->Add(m_pObject);
//}
