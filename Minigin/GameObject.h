#pragma once
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:

		template<typename Comp> Comp* AddComponent();
		template<typename Comp> Comp* GetComponent() const;
		template<typename Comp> void RemoveComponent();

		void Update(float deltaT);
		void Render() const;
		
		void SetDeleted(bool deleted);
		bool GetDeleted() const;

		void SetParent(GameObject* pNewParent);
		const std::vector<std::unique_ptr<GameObject>>& GetChildren() const { return m_pChildren; }

		GameObject* GetParent() const { return m_pParent; }

		GameObject();
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool m_Deleted{ false };

		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_pComponents;

		GameObject* m_pParent{ nullptr };
		std::vector<std::unique_ptr<GameObject>> m_pChildren{};

		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);
	};

	template <typename Comp>
	Comp* GameObject::AddComponent()
	{
		static_assert(std::is_base_of_v<Component, Comp>, "Comp must derive from Component");

		m_pComponents.emplace(typeid(Comp), std::make_unique<Comp>(this));

		return dynamic_cast<Comp*>(m_pComponents.at(typeid(Comp)).get());
	}

	template <typename Comp>
	Comp* GameObject::GetComponent() const
	{
		static_assert(std::is_base_of_v<Component, Comp>, "Comp must derive from ComponentBase");

		if (const auto it = m_pComponents.find(typeid(Comp)); it != m_pComponents.end())
			return dynamic_cast<Comp*>(it->second.get());

		return nullptr;
	}

	template <typename Comp>
	void GameObject::RemoveComponent()
	{
		if (const auto it = m_pComponents.find(typeid(Comp)); it != m_pComponents.end())
			m_pComponents.erase(it);
	}
}
