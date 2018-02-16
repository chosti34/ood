#pragma once

#include <functional>
#include <set>

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
	virtual void Update(const T& data) = 0;
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
		m_observers.insert(&observer);
	}

	void RemoveObserver(ObserverType& observer) override
	{
		m_observers.erase(&observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		// Используем копию списка, чтобы при удалении подписчика внутри его метода Update
		//  не происходило инвалидации итератора и падения программы.
		// Второй вариант: можно воспользоваться дополнительным списком и при удалении объекта заносить
		//  его в этот список. После выполнения цикла удалять из исходного списка тех подписчиков, которые
		//  оказались в дополнительном списке.
		auto observersCopy = m_observers;
		for (auto& observer : observersCopy)
		{
			observer->Update(data);
		}
	}

	size_t GetNotifiersCount()const
	{
		return m_observers.size();
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	std::set<ObserverType*> m_observers;
};
