#pragma once
#include <memory>
#include <map>
#include "Command.h"
#include "ThumbCommand.h"

namespace dae
{
	enum class KeyState;

	class Controller final
	{
	public:
		Controller();
		explicit Controller(int index);

		~Controller() = default;
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = default;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		enum class ControllerButton
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

		enum class ControllerAxis
		{
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200
		};

		void Update() const;
		void AddCommand(std::unique_ptr<Command> command, std::pair<KeyState, ControllerButton> button) const;
		void AddCommand(std::unique_ptr<ThumbCommand> command, ControllerAxis axis) const;
		void InvertAxis() const;

	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pControllerImpl;
	};
}
