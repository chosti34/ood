#include "stdafx.h"
#include "../WeatherData.h"
#include <vector>
#include <memory>
#include <numeric>

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
	int GetChangedData() const override
	{
		return m_data;
	}

	int m_data;
};

class DummyObserver : public IObserver<int>
{
public:
	DummyObserver(DummyObservable& observable, int priority, std::vector<DummyObserver*>* refs = nullptr)
		: m_observable(observable)
		, m_refs(refs)
	{
		m_observable.RegisterObserver(*this, priority);
	}

	~DummyObserver()
	{
		// Не должно вызвать падение программы
		m_observable.RemoveObserver(*this);
	}

	void Update(const int& data) override
	{
		if (m_refs != nullptr)
		{
			m_refs->push_back(this);
		}
	}

private:
	DummyObservable& m_observable;
	std::vector<DummyObserver*>* m_refs;
};
}

BOOST_AUTO_TEST_SUITE(ObserversPriorities)
	BOOST_AUTO_TEST_CASE(notifiers_are_updated_in_order_of_their_priority)
	{
		DummyObservable observable;
		std::vector<DummyObserver*> refs;

		std::vector<std::unique_ptr<DummyObserver>> observers;
		observers.push_back(std::make_unique<DummyObserver>(observable, -100, &refs));
		observers.push_back(std::make_unique<DummyObserver>(observable, -1, &refs));
		observers.push_back(std::make_unique<DummyObserver>(observable, 0, &refs));
		observers.push_back(std::make_unique<DummyObserver>(observable, 1, &refs));
		observers.push_back(std::make_unique<DummyObserver>(observable, 50, &refs));
		observers.push_back(std::make_unique<DummyObserver>(observable, std::numeric_limits<int>::max(), &refs));

		BOOST_CHECK_EQUAL(observable.GetNotifiersCount(), 6);
		observable.SetData(100);
		BOOST_CHECK_EQUAL(observable.GetNotifiersCount(), 6);
		BOOST_CHECK_EQUAL(refs.size(), 6u);

		// В переменной refs лежат ссылки (или указатели) на объекты из массива observers,
		// в порядке обхода вызова метода Update
		for (int i = 0; i < refs.size(); ++i)
		{
			BOOST_CHECK(refs[i] == observers[refs.size() - i - 1].get());
		}
	}
BOOST_AUTO_TEST_SUITE_END()
