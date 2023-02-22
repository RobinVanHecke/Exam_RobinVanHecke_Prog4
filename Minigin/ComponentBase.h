#pragma once
#include <string>

class ComponentBase
{
public:
	virtual void Update();

	ComponentBase() = default;
	virtual ~ComponentBase() = default;
	ComponentBase(const ComponentBase& other) = delete;
	ComponentBase(ComponentBase&& other) = delete;
	ComponentBase& operator=(const ComponentBase& other) = delete;
	ComponentBase& operator=(ComponentBase&& other) = delete;

protected:
	std::string m_typeName;
};

