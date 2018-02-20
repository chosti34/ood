#pragma once
#include "IObserver.h"
#include <unordered_map>

template <typename T>
class AbstractObservable : public IObservable<T>
{
public:
	bool RegisterObserver(IObserver<T>& observer, boost::signals2::connection& connection) override
	{
		auto found = m_connections.find(std::addressof(observer));
		if (found == m_connections.end())
		{
			connection = m_signal.connect(
				std::bind(&IObserver<T>::Update, std::addressof(observer), std::placeholders::_1, std::ref(*this)));
			m_connections.emplace(std::addressof(observer), connection);
			return true;
		}
		return false;
	}

	void RemoveObserver(IObserver<T>& observer) override
	{
		auto found = m_connections.find(std::addressof(observer));
		if (found != m_connections.end())
		{
			boost::signals2::connection& connection = found->second;
			if (connection.connected())
			{
				connection.disconnect();
			}
			m_connections.erase(found);
		}
	}

	void NotifyObservers() override
	{
		m_signal(GetChangedData());
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	boost::signals2::signal<void(const T& newData)> m_signal;
	std::unordered_map<IObserver<T>*, boost::signals2::connection> m_connections;
};
