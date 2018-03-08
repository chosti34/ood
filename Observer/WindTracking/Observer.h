#pragma once
#include <map>
#include <set>
#include <string>
#include <functional>

template <typename EventType, typename DataType>
class IObservable;

template <typename EventType, typename DataType>
class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void Update(const DataType& data, const IObservable<EventType, DataType>& observable) = 0;
};

template <typename EventType, typename DataType>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(const EventType& event, IObserver<EventType, DataType>& observer) = 0;
	virtual void RemoveObserver(const EventType& event, IObserver<EventType, DataType>& observer) = 0;
	virtual void NotifyObservers(const EventType& event) = 0;
};

template <typename EventType, typename DataType>
class AbstractObservable : public IObservable<EventType, DataType>
{
public:
	void RegisterObserver(const EventType& event, IObserver<EventType, DataType>& observer) override
	{
		auto found = m_observersMap.find(event);
		if (found != m_observersMap.end())
		{
			found->second.insert(std::addressof(observer));
		}
		else
		{
			std::set<IObserver<EventType, DataType>*> observers;
			observers.insert(std::addressof(observer));
			m_observersMap.emplace(event, observers);
		}
	}

	void RemoveObserver(const EventType& event, IObserver<EventType, DataType>& observer) override
	{
		auto found = m_observersMap.find(event);
		if (found != m_observersMap.end())
		{
			auto& observers = found->second;
			observers.erase(std::addressof(observer));
		}
	}

	void NotifyObservers(const EventType& event) override
	{
		DataType data = GetChangedData();
		auto found = m_observersMap.find(event);
		if (found != m_observersMap.end())
		{
			// Пробегаем по копии коллекции, чтобы позволить подписчикам отписываться внутри метода Update
			auto observers = found->second;
			for (auto& pObserver : observers)
			{
				pObserver->Update(data, *this);
			}
		}
	}

protected:
	virtual DataType GetChangedData()const = 0;

private:
	std::map<EventType, std::set<IObserver<EventType, DataType>*>> m_observersMap;
};
