#pragma once
#include <memory>
#include <vector>

#include "ButtonComponent.h"
#include "Singleton.h"
#include "Controller.h"

namespace dae
{
	enum class KeyState
	{
		Down,
		Pressed,
		Up
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class Key
		{
			A, B, C, D,
			E, F, G, H,
			I, J, K, L,
			M, N, O, P,
			Q, R, S, T,
			U, V, W, X,
			Y, Z, F1
		};

		bool ProcessInput();

		void AddController(std::unique_ptr<Controller> controller);
		int GetAmountOfControllers() const { return static_cast<int>(m_pControllers.size()); }

		void AddCommand(std::unique_ptr<Command> command, KeyState keyState, Key key);
		void RemoveCommands();

		void AddButton(ButtonComponent* pButton) { m_pButtons.push_back(pButton); }
		void RemoveButtons() { m_pButtons.clear(); }
		

	private:
		std::vector<std::unique_ptr<Controller>> m_pControllers;
		std::map<std::pair<KeyState, int>, std::unique_ptr<Command>> m_pKeyboardCommands;

		uint8_t m_PreviousKeyState[256]{};
		uint8_t m_CurrentKeyState[256]{};

		std::vector<ButtonComponent*> m_pButtons{};
		bool m_RemovedCommands{};

		void ControllerInput() const;
		void KeyboardInput();

		uint8_t m_KeyDown = 0x080;
		bool Down(const int key) const { return m_CurrentKeyState[key] & m_KeyDown && !(m_PreviousKeyState[key] & m_KeyDown); }
		bool Pressed(const int key) const { return m_CurrentKeyState[key] & m_KeyDown; }
		bool Up(const int key) const { return !(m_CurrentKeyState[key] & m_KeyDown) && m_PreviousKeyState[key] & m_KeyDown; }

		int KeyToInt(Key key) const;
	};
}