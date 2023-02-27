#pragma once
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "Transform.h"


#include "ComponentBase.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject // i know should be final here, but i couldnt get it to work with text component so i have it like this so it at least builds
	{
	public:

		template<typename Comp> Comp* AddComponent(Comp component);
		template<typename Comp> Comp* GetComponent() const;
		template<typename Comp> void RemoveComponent();


		virtual void Update(float deltaT);
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		void SetDeleted(bool deleted);
		bool GetDeleted() const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool m_Deleted{ false };

		std::unordered_map<std::type_index, ComponentBase*> m_Components;

		Transform m_Transform{};

		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
	};

	template <typename Comp>
	Comp* GameObject::AddComponent(Comp)
	{
		m_Components.emplace(typeid(Comp), new Comp);

		return new Comp;
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
		m_Components.erase(typeid(Comp));
	}
}
