#pragma once
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "ComponentBase.h"

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

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	

	private:
		bool m_Deleted{ false };

		std::unordered_map<std::type_index, ComponentBase*> m_Components;

		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren{ nullptr };

		void AddChild();
		void RemoveChild(GameObject* pChild);
	};

	template <typename Comp>
	Comp* GameObject::AddComponent()
	{
		m_Components.emplace(typeid(Comp), new Comp{ this });

		return dynamic_cast<Comp*>(m_Components.at(typeid(Comp)));
	}

	template <typename Comp>
	Comp* GameObject::GetComponent() const
	{
		static_assert(std::is_base_of_v<ComponentBase, Comp>, "Component must derive from ComponentBase");

		const auto it = m_Components.find(typeid(Comp));

		if (it != m_Components.end())
		{
			return dynamic_cast<Comp*>(it->second);
		}
		return nullptr;
	}

	template <typename Comp>
	void GameObject::RemoveComponent()
	{
		delete m_Components.at(typeid(Comp));
		m_Components.erase(typeid(Comp));
	}
}
