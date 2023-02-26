#pragma once
class ComponentBase
{
public:
	ComponentBase() = default;
	virtual ~ComponentBase();
	ComponentBase(const ComponentBase& other) = delete;
	ComponentBase(ComponentBase&& other) = delete;
	ComponentBase& operator=(const ComponentBase& other) = delete;
	ComponentBase& operator=(ComponentBase&& other) = delete;

private:

};

