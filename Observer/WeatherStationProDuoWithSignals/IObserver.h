#pragma once
#include <boost/signals2/signal.hpp>

template <typename T>
class IObservable;

template <typename T>
class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void Update(const T& data, const IObservable<T>& observable) = 0;
};

template <typename T>
class IObservable
{
public:
	virtual bool RegisterObserver(IObserver<T>& observer, boost::signals2::connection& connection) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
};
