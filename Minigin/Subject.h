#pragma once
#include <vector>

#include "Observer.h"

namespace dae
{
	template<class T>
	class Subject final
	{
	public:
		Subject() = default;
		~Subject() = default;

		void AddObserver(Observer<T>* pobserver)
		{
			for (const auto & pOther : m_pObservers)
				if (pOther == pobserver)
					return;

			m_pObservers.push_back(pobserver);
		}

		void RemoveObserver(Observer<T>* pObserver)
		{
			for (const auto & pOther : m_pObservers)
			{
				if (pOther == pObserver)
				{
					delete pOther;
					pOther = nullptr;
					break;
				}
			}

			m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), nullptr), m_pObservers.end());
		}

	protected:
		void Notify(T* pData, int id)
		{
			for (const auto & pObserver : m_pObservers)
				pObserver->Notify(pData, id);
			
		}

	private:
		std::vector<Observer<T>*> m_pObservers{};
	};
}
