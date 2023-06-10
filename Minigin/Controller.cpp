#include "Controller.h"
#include <cstdlib>
#include <algorithm>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

namespace dae
{
	class Controller::ControllerImplementation
	{
    public:
        ControllerImplementation(const unsigned int index) : m_Index{ index } {}

        void Update()
        {
            m_PreviousState = m_CurrentState;
            XInputGetState(m_Index, &m_CurrentState);

            const auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
            m_ButtonsDown = buttonChanges & m_CurrentState.Gamepad.wButtons;
            m_ButtonsUp = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
        }

        void SetDeadZone(const float percentage) { m_DeadZone = percentage; }

        bool OnButton(const unsigned int button) const
        {
            return m_CurrentState.Gamepad.wButtons & button;
        }

        bool OnButtonUp(const unsigned int button) const
        {
            return m_ButtonsUp & button;
        }

        bool OnButtonDown(const unsigned int button) const
        {
            return m_ButtonsDown & button;
        }

        float GetAxis(const bool left, const bool x) const
        {
            constexpr float ceilPercentage{ 0.9f };
            constexpr SHORT ceilValue{ static_cast<SHORT>(ceilPercentage * MAXSHORT) };

            const auto axisValue
            {
                x
                ? (left ? m_CurrentState.Gamepad.sThumbLX : m_CurrentState.Gamepad.sThumbRX)
                : (left ? m_CurrentState.Gamepad.sThumbLY : m_CurrentState.Gamepad.sThumbRY)
            };

            const SHORT sign{ axisValue == 0 ? 0 : static_cast<SHORT>(abs(axisValue) / axisValue) };
            const SHORT deadZoneValue{ static_cast<SHORT>(m_DeadZone * MAXSHORT) };

            const SHORT clamped{ std::clamp(static_cast<SHORT>(abs(axisValue - sign)), deadZoneValue, ceilValue) };
            return static_cast<float>(clamped - deadZoneValue) / (ceilValue - deadZoneValue) * sign;
        }

        float GetAxis(const unsigned int button) const
        {
            switch (button)
            {
            case XINPUT_GAMEPAD_LEFT_SHOULDER:
                return static_cast<float>(m_CurrentState.Gamepad.bLeftTrigger) / MAXBYTE;
            case XINPUT_GAMEPAD_RIGHT_SHOULDER:
                return static_cast<float>(m_CurrentState.Gamepad.bRightTrigger) / MAXBYTE;

            default: ;
            }
            return 0.0f;
        }

    private:
        unsigned int m_Index{};

        XINPUT_STATE m_PreviousState{};
        XINPUT_STATE m_CurrentState{};

        unsigned int m_ButtonsDown{};
        unsigned int m_ButtonsUp{};

        float m_DeadZone{ 0.25f };
	};

    Controller::Controller(const unsigned index) : m_pImplementation{ new ControllerImplementation{ index} }
	{
	}

	void Controller::Update() const
	{
        m_pImplementation->Update();
	}

	void Controller::SetDeadZone(const float percentage) const
	{
        m_pImplementation->SetDeadZone(percentage);
	}

	bool Controller::OnButton(const unsigned button) const
	{
        return m_pImplementation->OnButton(button);
	}

	bool Controller::OnButtonUp(const unsigned button) const
	{
        return m_pImplementation->OnButtonUp(button);
	}

	bool Controller::OnButtonDown(const unsigned button) const
	{
        return m_pImplementation->OnButtonDown(button);
	}

	float Controller::GetAxis(const unsigned thumbStick, const bool x) const
	{
        return m_pImplementation->GetAxis(thumbStick == XINPUT_GAMEPAD_LEFT_THUMB, x);
	}

	float Controller::GetAxis(const unsigned button) const
	{
        return m_pImplementation->GetAxis(button);
	}
}


