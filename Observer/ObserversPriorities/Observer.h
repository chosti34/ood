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

template <typename KeyType, typename ValueType>
class MultiKeySingleValueMap
{
public:
	MultiKeySingleValueMap()
		: m_keyToValue()
		, m_valueToKey()
	{
	}

	bool Insert(const KeyType& key, const ValueType& value)
	{
		auto found = m_valueToKey.find(value);
		if (found == m_valueToKey.end())
		{
			auto pair = m_valueToKey.emplace(value, key);
			try
			{
				// can this operation throw any exception?
				m_keyToValue.emplace(key, value);
				return true;
			}
			catch (...)
			{
				// rollback
				m_valueToKey.erase(pair.first);
				throw;
			}
		}
		return false;
	}

	bool Remove(const ValueType& value)
	{
		auto found = m_valueToKey.find(value);
		if (found != m_valueToKey.end())
		{
			auto range = m_keyToValue.equal_range(found->second);
			for (auto it = range.first; it != range.second; ++it)
			{
				if (it->second == value)
				{
					m_keyToValue.erase(it);
					m_valueToKey.erase(found);
					return true;
				}
			}
			assert(false);
		}
		return false;
	}

	std::multimap<KeyType, ValueType> GetKeyToValueMapCopy()
	{
		return m_keyToValue;
	}

private:
	std::multimap<KeyType, ValueType> m_keyToValue;
	std::unordered_map<ValueType, KeyType> m_valueToKey;
};

template <typename T>
class AbstractObservable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		m_observersMap.Insert(priority, std::addressof(observer));
	}

	void RemoveObserver(ObserverType& observer) override
	{
		m_observersMap.Remove(std::addressof(observer));
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto copy = m_observersMap.GetKeyToValueMapCopy();
		for (auto it = copy.rbegin(); it != copy.rend(); ++it)
		{
			ObserverType* observer = it->second;
			observer->Update(data);
		}
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	MultiKeySingleValueMap<int, ObserverType*> m_observersMap;
};
