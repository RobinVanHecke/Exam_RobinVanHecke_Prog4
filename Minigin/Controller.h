#pragma once
#include <memory>

namespace dae
{
	class Controller final
	{
		class ControllerImplementation;
		std::unique_ptr<ControllerImplementation> m_pImplementation;

	public:
		Controller(unsigned int index);
		~Controller() = default;

		void Update() const;
		void SetDeadZone(float percentage) const;

		bool OnButton(unsigned int button) const;
		bool OnButtonUp(unsigned int button) const;
		bool OnButtonDown(unsigned int button) const;
		
		float GetAxis(unsigned int thumbStick, bool x) const;
		float GetAxis(unsigned int button) const;
	};
}
