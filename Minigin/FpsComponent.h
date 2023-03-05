#pragma once
#include "ComponentBase.h"

class FpsComponent final : public ComponentBase
{
public:
	FpsComponent(dae::GameObject* gameObject);

	void Update(float deltaT) override;
	float GetFps() const { return m_Fps; }

private:
	float m_Fps{0};
};
