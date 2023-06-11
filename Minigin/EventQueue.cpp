#include "EventQueue.h"

void dae::EventQueue::Update()
{
	if (!m_Init)
		m_pEvents.resize(m_Size);

	while (m_Front != m_Back)
	{
		std::unique_ptr<std::tuple<std::any, int, bool>> event = std::move(m_pEvents[m_Front]);

		if (event == nullptr)
			return;

		for (const auto pListener : m_pListeners)
		{
			if (pListener)
				pListener->OnEvent(std::get<0>(*event), std::get<1>(*event), std::get<2>(*event));

			if (m_ListenerRemoved)
			{
				m_ListenerRemoved = false;
				break;
			}
		}

		m_pEvents[m_Front] = nullptr;
		m_Front = (m_Front + 1) % m_Size;
	}

	if (!m_pListeners.empty())
		std::erase_if(m_pListeners, [&](const EventListener* pObserver) {return pObserver == nullptr; });
}

void dae::EventQueue::RemoveListener(const EventListener* pObserver)
{
	for (auto & pListener : m_pListeners)
		if (pListener == pObserver)
		{
			m_ListenerRemoved = true;
			pListener = nullptr;
		}
}

void dae::EventQueue::AddEvent(std::any pData, int id, bool engineEvent)
{
	if ((m_Back + 1) % m_Size == m_Front)
	{
		m_Size += m_Size / 2;
		m_pEvents.resize(m_Size);
	}

	m_pEvents[m_Back] = std::move(std::make_unique<std::tuple<std::any, int, bool>>(pData, id, engineEvent));
	m_Back = (m_Back + 1) % m_Size;
}