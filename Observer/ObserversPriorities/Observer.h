#pragma once
#include <map>
#include <cassert>
#include <functional>
#include <unordered_map>

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
	virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
};

template <typename T>
class AbstractObservable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		// Подписываем наблюдателя только в том случае, если он ещё не подписан
		//  на данного издателя
		auto foundPriority = m_observerToPriorityMap.find(std::addressof(observer));
		if (foundPriority == m_observerToPriorityMap.end())
		{
			auto inserted = m_priorityToObserverMap.emplace(priority, std::addressof(observer));
			assert(inserted->second);
			try
			{
				// Может ли в этой строке выбросится исключение?
				// Если да, то ловим его и производим rollback к исходному состоянию
				m_observerToPriorityMap.emplace(std::addressof(observer), priority);
			}
			catch (...)
			{
				m_priorityToObserverMap.erase(inserted);
				throw;
			}
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		// Класс может содержать разные ссылки с одинаковым приоритетом,
		//  однако не может содержать одинаковые ссылки.
		// Первая найденная ссылка (указатель) в коллекции должна быть одна
		auto found = m_observerToPriorityMap.find(std::addressof(observer));
		if (found != m_observerToPriorityMap.end())
		{
			auto range = m_priorityToObserverMap.equal_range(found->second);
			for (auto it = range.first; it != range.second; ++it)
			{
				if (std::addressof(observer) == it->second)
				{
					m_priorityToObserverMap.erase(it);
					m_observerToPriorityMap.erase(std::addressof(observer));
					return;
				}
			}
			assert(false);
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		// Пробегаем по копии коллекции, чтобы позволить подписчикам отписываться внутри метода Update
		auto observersCopy = m_priorityToObserverMap;
		for (auto it = observersCopy.rbegin(); it != observersCopy.rend(); ++it)
		{
			it->second->Update(data);
		}
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	// Класс подписывает контракт:
	//  мы можем хранить различные ссылки с одинаковым приоритетом,
	//  однако запрещаем хранить одинаковые ссылки с любым приоритетом
	std::multimap<int, ObserverType*> m_priorityToObserverMap;
	std::unordered_map<ObserverType*, int> m_observerToPriorityMap;
};
