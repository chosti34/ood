#pragma once
#include <map>
#include <set>
#include <string>
#include <functional>

// Тип события:
//  1 - изменилось значение температуры или атмосферного давления
//  2 - изменилось любое значение
enum class EventType
{
	TemperatureOrPressureChange,
	AnyChange
};

template <typename T>
class IObservable;

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void Update(const T& data, const IObservable<T>& observable) = 0;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения наблюдателям,
а также инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(EventType event, IObserver<T>& observer) = 0;
	virtual void RemoveObserver(EventType event, IObserver<T>& observer) = 0;
	virtual void NotifyObservers(EventType event) = 0;
};

template <typename T>
class AbstractObservable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(EventType event, ObserverType& observer) override
	{
		auto found = m_observersMap.find(event);
		if (found != m_observersMap.end())
		{
			found->second.insert(std::addressof(observer));
		}
		else
		{
			std::set<ObserverType*> observers;
			observers.insert(std::addressof(observer));
			m_observersMap.emplace(event, observers);
		}
	}

	void RemoveObserver(EventType event, ObserverType& observer) override
	{
		auto found = m_observersMap.find(event);
		if (found != m_observersMap.end())
		{
			auto& observers = found->second;
			observers.erase(std::addressof(observer));
		}
	}

	void NotifyObservers(EventType event) override
	{
		T data = GetChangedData();
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
	virtual T GetChangedData()const = 0;

private:
	std::map<EventType, std::set<ObserverType*>> m_observersMap;
};
