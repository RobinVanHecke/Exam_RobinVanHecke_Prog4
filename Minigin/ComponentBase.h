#pragma once
#include <memory>

namespace dae
{
	class GameObject;
}

class ComponentBase
{
public:
	virtual void Update();

	ComponentBase(std::shared_ptr<dae::GameObject> gameObject);
	virtual ~ComponentBase() = default;

	ComponentBase(const ComponentBase& other) = delete;
	ComponentBase(ComponentBase&& other) = delete;
	ComponentBase& operator=(const ComponentBase& other) = delete;
	ComponentBase& operator=(ComponentBase&& other) = delete;

	//TODO make protected get owner function

private:
	std::shared_ptr<dae::GameObject> m_pOwner{ nullptr };

};

