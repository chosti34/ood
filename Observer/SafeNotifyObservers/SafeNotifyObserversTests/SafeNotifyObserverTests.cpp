#include "stdafx.h"
#include "../WeatherData.h"

namespace
{
class DummyObservable : public AbstractObservable<int>
{
public:
	void SetData(int data)
	{
		m_data = data;
		NotifyObservers();
	}

private:
	virtual int GetChangedData() const override
	{
		return m_data;
	}

	int m_data;
};

class DummyObserver : public IObserver<int>
{
public:
	DummyObserver(DummyObservable& observable, bool eraseOnUpdate)
		: m_observable(observable)
		, m_eraseOnUpdate(eraseOnUpdate)
	{
		m_observable.RegisterObserver(*this);
	}

	~DummyObserver()
	{
		// Не должно вызвать падение программы
		m_observable.RemoveObserver(*this);
	}

	void Update(const int& data) override
	{
		if (m_eraseOnUpdate)
		{
			// Не должно вызвать падение программы
			m_observable.RemoveObserver(*this);
		}
	}

	void SetEraseOnUpdate(bool eraseOnUpdate)
	{
		m_eraseOnUpdate = eraseOnUpdate;
	}

private:
	DummyObservable& m_observable;
	bool m_eraseOnUpdate;
};
}

BOOST_AUTO_TEST_SUITE(WeatherStation)
	BOOST_AUTO_TEST_CASE(notifiers_can_remove_themselves_from_observables_list_safely)
	{
		DummyObservable observable;
		DummyObserver observer1(observable, true);
		DummyObserver observer2(observable, false);
		observable.SetData(123);
		BOOST_CHECK_EQUAL(observable.GetNotifiersCount(), 1);
		observer2.SetEraseOnUpdate(true);
		observable.SetData(456);
		BOOST_CHECK_EQUAL(observable.GetNotifiersCount(), 0);
	}
BOOST_AUTO_TEST_SUITE_END()
