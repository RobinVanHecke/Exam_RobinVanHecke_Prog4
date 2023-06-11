#pragma once

namespace dae
{
	template<typename Data>
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(Data* pData, int id) = 0;
	};
}
