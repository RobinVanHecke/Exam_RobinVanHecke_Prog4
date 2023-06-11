#pragma once

namespace dae
{
	class GameObject;
}


class Component
{
public:
	virtual void Update(float /*deltaT*/) {}
	virtual void Render() const{}
	virtual void OnGUI() {}

	Component() = default;
	explicit Component(dae::GameObject* gameObject): m_pOwner( gameObject) {}
	virtual ~Component() = default;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

protected:
	dae::GameObject* GetOwner() const { return m_pOwner; }

private:
	dae::GameObject* m_pOwner{ nullptr };

};

