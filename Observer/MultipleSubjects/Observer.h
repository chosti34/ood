#pragma once

#include <functional>
#include <set>
#include <string>

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
	virtual void Update(const T& data, IObservable<T>& observable) = 0;
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
	virtual void RegisterObserver(IObserver<T>& observer) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
};

template <typename T>
class AbstractObservable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType& observer) override
	{
		m_observers.insert(std::addressof(observer));
	}

	void RemoveObserver(ObserverType& observer) override
	{
		m_observers.erase(std::addressof(observer));
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		// Пробегаем по копии коллекции, чтобы позволить подписчикам отписываться внутри метода Update
		auto observersCopy = m_observers;
		for (auto& observer : observersCopy)
		{
			observer->Update(data, *this);
		}
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	std::set<ObserverType*> m_observers;
};
