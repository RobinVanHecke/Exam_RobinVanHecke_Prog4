#pragma once
#include "Singleton.h"

namespace dae
{
	class Gameobject;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

	};
}