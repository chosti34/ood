#pragma once

#include <functional>
#include <set>
#include <string>

template <typename T>
class IObservable;

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
	virtual void Update(const T& data, IObservable<T>& observable) = 0;
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
		// ��������� �� ����� ���������, ����� ��������� ����������� ������������ ������ ������ Update
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
