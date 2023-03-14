#pragma once
#include <string>

#include "Component.h"

class FpsComponent final : public Component
{
public:
	FpsComponent(dae::GameObject* gameObject);

	void Update(float deltaT) override;
	float GetFps() const { return m_Fps; }

private:
	float m_Fps{0};
	std::string m_FpsString;
};
