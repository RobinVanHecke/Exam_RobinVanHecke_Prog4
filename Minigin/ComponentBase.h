#pragma once

namespace dae
{
	class GameObject;
}


class ComponentBase
{
public:
	virtual void Update(float /*deltaT*/) {}
	virtual void Render() const{}

	explicit ComponentBase(dae::GameObject* gameObject): m_pOwner( gameObject) {}
	virtual ~ComponentBase() = default;

	ComponentBase(const ComponentBase& other) = delete;
	ComponentBase(ComponentBase&& other) = delete;
	ComponentBase& operator=(const ComponentBase& other) = delete;
	ComponentBase& operator=(ComponentBase&& other) = delete;

protected:
	dae::GameObject* GetOwner() const { return m_pOwner; }

private:
	dae::GameObject* m_pOwner{ nullptr };

};

