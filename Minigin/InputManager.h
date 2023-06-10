#pragma once
#include "Singleton.h"
#include "DataCommand.h"
#include "Controller.h"

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <set>

namespace dae
{
	class Gameobject;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		enum class InputType
		{
			OnButton, OnButtonUp, OnButtonDown
		};

		enum class GamepadButton
		{
			DpadUp = 0x0001,
			DpadDown = 0x0002,
			DpadLeft = 0x0004,
			DpadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			A = 0x1000,
			B = 0x2000,
			X = 0x4000,
			Y = 0x8000
		};

		enum class GamepadAxis
		{
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200
		};
	};
}