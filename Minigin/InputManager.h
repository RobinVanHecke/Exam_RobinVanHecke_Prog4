#pragma once
#include <memory>
#include <vector>

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
		bool ProcessInput();

		int GetAmountOfControllers() const { return static_cast<int>(m_pControllers.size()); }

	private:
		std::vector<std::unique_ptr<Controller>> m_pControllers;

	};
}