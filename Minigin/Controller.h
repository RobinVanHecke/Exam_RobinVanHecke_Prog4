#pragma once
#include <memory>

namespace dae
{
	enum class KeyState;

	class Controller final
	{
	public:
		Controller();
		explicit Controller(int index);

		~Controller();
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = default;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		enum class ControllerKey : unsigned int
		{
			
		};
	};
}
