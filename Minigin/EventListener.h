#pragma once
#include <any>

namespace dae
{
	class EventListener
	{
	public:
		virtual ~EventListener() = default;
		virtual void OnEvent(std::any data, int id, bool engineEvent) = 0;
	};
}
