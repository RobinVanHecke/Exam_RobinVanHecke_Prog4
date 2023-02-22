#pragma once
#include <memory>
#include <unordered_map>

#include "ComponentBase.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		void Update();

		template <typename T> T* AddComponent( T component);
		template <typename T> T* GetComponent() const;
		template <typename T> void RemoveComponent();

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::unordered_map<std::type_info, ComponentBase> *m_pComponents;

		GameObject* m_pOtherGameobject;
	};

	template <typename T>
	T* GameObject::AddComponent(T component)
	{
		m_pComponents->emplace(typeid(component), new T);

		return *component;
	}

	template <typename T>
	T* GameObject::GetComponent() const
	{
		return m_pComponents->at(typeid(T));
	}

	template <typename T>
	void GameObject::RemoveComponent()
	{
		m_pComponents->erase(typeid(T));
	}
}
