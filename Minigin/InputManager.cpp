#include <SDL.h>
#include "InputManager.h"

#include <Windows.h>

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (e.button.button == SDL_BUTTON_LEFT)
				for (const auto & pButton : m_pButtons)
					pButton->OnMouseClick(glm::vec2(static_cast<float>(e.button.x), static_cast<float>(e.button.y)));
		}
		// etc...
	}

	ControllerInput();
	KeyboardInput();

	return true;
}

void dae::InputManager::AddController(std::unique_ptr<Controller> controller)
{
	m_pControllers.push_back(std::move(controller));
}

void dae::InputManager::AddCommand(std::unique_ptr<Command> command, KeyState keyState, Key key)
{
	std::pair action{ keyState, KeyToInt(key) };
	m_pKeyboardCommands.insert(std::pair(action, std::move(command)));
}

void dae::InputManager::RemoveCommands()
{
	m_pKeyboardCommands.clear();
	m_pControllers.clear();
	m_RemovedCommands = true;
}

void dae::InputManager::ControllerInput() const
{
	for (const auto & pController : m_pControllers)
		pController->Update();
}

void dae::InputManager::KeyboardInput()
{
	memcpy(m_PreviousKeyState, m_CurrentKeyState, sizeof m_PreviousKeyState);
	//GetKeyboardState(m_CurrentKeyState);

	for (const auto & [keyState, command] : m_pKeyboardCommands)
	{
		switch (keyState.first)
		{
		case KeyState::Down:
			if (Down(keyState.second))
				command->Execute();
			break;

		case KeyState::Pressed:
			if (Pressed(keyState.second))
				command->Execute();
			break;

		case KeyState::Up:
			if (Up(keyState.second))
				command->Execute();
			break;
		}

		if (m_RemovedCommands)
		{
			m_RemovedCommands = false;
			break;
		}
	}
}

int dae::InputManager::KeyToInt(const Key key) const
{
	switch (key)
	{
	case Key::A: 
		return 'A';
	case Key::B: 
		return 'B';
	case Key::C: 
		return 'C';
	case Key::D: 
		return 'D';
	case Key::E: 
		return 'E';
	case Key::F: 
		return 'F';
	case Key::G: 
		return 'G';
	case Key::H: 
		return 'H';
	case Key::I: 
		return 'I';
	case Key::J: 
		return 'J';
	case Key::K: 
		return 'K';
	case Key::L: 
		return 'L';
	case Key::M: 
		return 'M';
	case Key::N: 
		return 'N';
	case Key::O: 
		return 'O';
	case Key::P: 
		return 'P';
	case Key::Q: 
		return 'Q';
	case Key::R: 
		return 'R';
	case Key::S: 
		return 'S';
	case Key::T: 
		return 'T';
	case Key::U: 
		return 'U';
	case Key::V: 
		return 'V';
	case Key::W: 
		return 'W';
	case Key::X: 
		return 'X';
	case Key::Y: 
		return 'Y';
	case Key::Z: 
		return 'Z';
	case Key::F1: 
		return VK_F1;
	}

	return -1;
}
