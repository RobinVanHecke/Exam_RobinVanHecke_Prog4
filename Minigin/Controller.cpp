#include "Controller.h"
#include <Windows.h>
#include <XInput.h>

#include "InputManager.h"

namespace dae
{
	class Controller::ControllerImpl final
	{
	public:
		ControllerImpl(const int index)
		{
			if (index == -1)
				m_Index = InputManager::GetInstance().GetAmountOfControllers();
			else
				m_Index = index;
		}

		~ControllerImpl() = default;
		ControllerImpl(const ControllerImpl& other) = delete;
		ControllerImpl(ControllerImpl&& other) = default;
		ControllerImpl& operator=(const ControllerImpl& other) = delete;
		ControllerImpl& operator=(ControllerImpl&& other) = delete;


		void Input()
		{
			if (m_Index < 0)
				return;

			ButtonCommands();
			AxisCommands();
		}

		void ButtonCommands()
		{
			CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
			XInputGetState(m_Index, &m_CurrentState);

			const auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
			m_ReleasedFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
			m_PressedFrame = buttonChanges & ~m_CurrentState.Gamepad.wButtons;

			for (const auto & [button, command] : m_ButtonCommands)
			{
				switch (button.first)
				{
				case KeyState::Down:
					if (ButtonDown(button.second))
						command->Execute();
					break;

				case KeyState::Pressed:
					if (ButtonPressed(button.second))
						command->Execute();
					break;

				case KeyState::Up:
					if (ButtonDown(button.second))
						command->Execute();
					break;
				}
			}
		}

		void AxisCommands()
		{
			constexpr  float epsilon{ 0.01f };

			for (const auto & [axis, command] : m_AxisCommands)
			{
				glm::vec2 thumbDir;

				switch (axis)
				{
				case ControllerAxis::LeftThumb: case ControllerAxis::RightThumb:
					thumbDir = GetThumbDir(axis);

					if (abs(thumbDir.x) > epsilon || abs(thumbDir.y) > epsilon)
					{
						command->SetDirection(thumbDir);
						command->Execute();
					}
					break;
				default: ;
				}
			}
		}

		glm::vec2 GetThumbDir(const ControllerAxis thumb) const
		{
			glm::vec2 thumbDir{};

			switch (thumb)
			{
			case ControllerAxis::LeftThumb:
				thumbDir = glm::vec2(m_CurrentState.Gamepad.sThumbLX, m_CurrentState.Gamepad.sThumbLY);
				break;

			case ControllerAxis::RightThumb:
				thumbDir = glm::vec2(m_CurrentState.Gamepad.sThumbRX, m_CurrentState.Gamepad.sThumbRY);
				break;
			default: ;
			}

			if (m_Inverted)
				thumbDir.y *= -1;

			const float deadZone = 0.15f * m_MaxThumbValue;

			if (abs(thumbDir.x) < deadZone && abs(thumbDir.y) < deadZone)
				return {0.f, 0.f};

			if (abs(thumbDir.x) < deadZone)
				thumbDir.x = .0f;
			else if (abs(thumbDir.y) < deadZone)
				thumbDir.y = .0f;

			return (thumbDir - deadZone) / (m_MaxThumbValue - deadZone);
		}

		void AddCommand(std::unique_ptr<Command> command, std::pair<KeyState, ControllerButton> button)
		{
			m_ButtonCommands.insert(std::pair(button, std::move(command)));
		}

		void AddCommand(std::unique_ptr<ThumbCommand> command, ControllerAxis axis)
		{
			m_AxisCommands.insert(std::pair(axis, std::move(command)));
		}

		void Invert() { m_Inverted = true; }

	private:
		int m_Index;
		XINPUT_STATE m_PreviousState{}, m_CurrentState{};
		unsigned int m_PressedFrame{}, m_ReleasedFrame{};

		std::map<std::pair<KeyState, ControllerButton>, std::unique_ptr<Command>> m_ButtonCommands{};
		std::map<ControllerAxis, std::unique_ptr<ThumbCommand>> m_AxisCommands{};

		const float m_MaxThumbValue{ 32767.f }, m_MinThumbValue{ -32768.f };

		bool m_Inverted{};

		bool ButtonDown(ControllerButton button) const { return m_PressedFrame & static_cast<unsigned int>(button); }
		bool ButtonPressed(ControllerButton button) const { return m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button); }
		bool ButtonUp(ControllerButton button) const { return m_ReleasedFrame & static_cast<unsigned int>(button); }
	};

	Controller::Controller() : m_pControllerImpl{ std::make_unique<ControllerImpl>(-1)}
	{
	}

	Controller::Controller(int index) : m_pControllerImpl{ std::make_unique<ControllerImpl>(index) }
	{
	}

	Controller::~Controller() = default;

	void Controller::Update() const
	{
		m_pControllerImpl->Input();
	}

	void Controller::AddCommand(std::unique_ptr<Command> command, const std::pair<KeyState, ControllerButton> button) const
	{
		m_pControllerImpl->AddCommand(std::move(command), button);
	}

	void Controller::AddCommand(std::unique_ptr<ThumbCommand> command, const ControllerAxis axis) const
	{
		m_pControllerImpl->AddCommand(std::move(command), axis);
	}

	void Controller::InvertAxis() const
	{
		m_pControllerImpl->Invert();
	}
}
