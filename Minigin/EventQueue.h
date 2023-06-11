#pragma once
#include <vector>
#include <tuple>
#include <any>
#include <memory>

#include "Singleton.h"
#include "EventListener.h"

namespace dae
{
	class EventQueue final : public Singleton<EventQueue>
	{
	public:
		EventQueue() = default;

		void Update();

		void AddListener(EventListener* pObserver) { m_pListeners.push_back(pObserver); }
		void RemoveListener(const EventListener* pObserver);

		void AddEvent(const std::any& pData, int id, bool engineEvent);

	private:
		std::vector<EventListener*> m_pListeners{};
		std::vector<std::unique_ptr<std::tuple<std::any, int, bool>>> m_pEvents{};

		bool m_Init{};

		int m_Front{}, m_Back{};
		int m_Size{ 10 };

		bool m_ListenerRemoved{};
	};
}
