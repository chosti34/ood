#pragma once

#include <functional>
#include <map>
#include <unordered_map>
#include <cassert>

/*
��������� ��������� IObserver. ��� ������ ������������� �����,
�������� �������� ����������� �� ���������������� IObservable
���������� ������� �������� ��� ���������,
������������� ����������� � ����� Update
*/
template <typename T>
class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void Update(const T& data) = 0;
};

/*
��������� ��������� IObservable. ��������� ����������� � ���������� �� ���������� ������������,
� ����� ������������ �������� ����������� ������������������ ������������.
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
		auto found = m_priorities.find(&observer);
		if (found == m_priorities.end())
		{
			m_observers.insert(std::make_pair(priority, &observer));
			m_priorities.insert(std::make_pair(&observer, priority));
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		// ����� ����� ��������� ������ ������ � ���������� �����������,
		//  ������ �� ����� ��������� ���������� ������.
		// ������ ��������� ������ (���������) � ��������� ������ ���� ����
		auto found = m_priorities.find(&observer);
		if (found != m_priorities.end())
		{
			auto range = m_observers.equal_range(found->second);
			for (auto it = range.first; it != range.second; ++it)
			{
				if (&observer == it->second)
				{
					m_observers.erase(it->first);
					m_priorities.erase(&observer);
					return;
				}
			}
			assert(false);
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		// ��������� �� ����� ���������, ����� ��������� ����������� ������������ ������ ������ Update
		auto observersCopy = m_observers;
		for (auto it = observersCopy.rbegin(); it != observersCopy.rend(); ++it)
		{
			it->second->Update(data);
		}
	}

	size_t GetNotifiersCount()const
	{
		return m_observers.size();
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	// ����� ����������� ��������:
	//  �� ����� ������� ��������� ������ � ���������� �����������,
	//  ������ ��������� ������� ���������� ������ � ����� �����������
	std::multimap<int, ObserverType*> m_observers;
	std::unordered_map<ObserverType*, int> m_priorities;
};
