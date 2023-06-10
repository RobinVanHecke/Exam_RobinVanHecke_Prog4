#pragma once
#include "Command.h"

namespace dae
{
	template<class Com>
	class DataCommand : public Command
	{
	public:
		virtual ~DataCommand() = default;
		virtual  void Execute() = 0;

		Com& GetData() { return m_Data; }

	private:
		Com m_Data{};
	};
}
