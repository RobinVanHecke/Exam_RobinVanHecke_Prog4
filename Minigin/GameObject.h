#pragma once
#include <memory>
#include "Transform.h"

#include <unordered_map>
#include "ComponentBase.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject 
	{
	public:

		template<typename T> T* AddComponent(T component);
		template<typename T> T* GetComponent() const;
		template<typename T> void RemoveComponent();


		virtual void Update();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:

		std::unordered_map<std::type_info, ComponentBase>* m_pComponents;


		Transform m_transform{};

		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
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
