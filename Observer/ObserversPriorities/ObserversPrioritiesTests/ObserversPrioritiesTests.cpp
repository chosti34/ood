#include "stdafx.h"
#include "../Observer.h"
#include <vector>
#include <memory>
#include <numeric>
#include <boost/test/output_test_stream.hpp>

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
	DummyObserver(DummyObservable& observable, int priority, const std::string& name,
		boost::test_tools::output_test_stream& strm)
		: m_observable(observable)
		, m_name(name)
		, m_strm(strm)
	{
		m_observable.RegisterObserver(*this, priority);
	}

	~DummyObserver()
	{
		// Не должно вызвать падение программы даже если мы отписались заранее
		m_observable.RemoveObserver(*this);
	}

	void Update(const int& data) override
	{
		(void)data;
		m_strm << m_name;
	}

private:
	DummyObservable& m_observable;
	boost::test_tools::output_test_stream& m_strm;
	std::string m_name;
};
}

BOOST_AUTO_TEST_SUITE(ObserversPrioritiesTaskTestSuite)
	BOOST_AUTO_TEST_CASE(subscribers_cannot_register_to_notifiers_twice_or_more_times)
	{
		boost::test_tools::output_test_stream output;

		DummyObservable observable;
		DummyObserver observer1(observable, 10, "a", output);
		DummyObserver observer2(observable, 30, "b", output);

		observable.RegisterObserver(observer1, 10);
		observable.RegisterObserver(observer2, 30);

		BOOST_CHECK(output.is_empty());
		observable.SetData(10);
		BOOST_CHECK(output.is_equal("ba"));
	}

	BOOST_AUTO_TEST_CASE(subscribers_with_same_priorities_will_be_notified_in_reversed_register_order)
	{
		boost::test_tools::output_test_stream output;

		DummyObservable observable;
		DummyObserver observer1(observable, 10, "a", output);
		DummyObserver observer2(observable, 10, "b", output);
		DummyObserver observer3(observable, 10, "c", output);
		DummyObserver observer4(observable, 10, "d", output);
		observable.RemoveObserver(observer4);

		BOOST_CHECK(output.is_empty());
		observable.SetData(100500);
		// Все подписчики с равным приоритетом будут оповещены в порядке, обратном порядку подписки
		BOOST_CHECK(output.is_equal("cba"));
	}

	BOOST_AUTO_TEST_CASE(subscribers_are_updated_in_order_of_their_priority)
	{
		boost::test_tools::output_test_stream output;

		DummyObservable observable;
		std::vector<std::unique_ptr<DummyObserver>> observers;
		observers.push_back(std::make_unique<DummyObserver>(observable, std::numeric_limits<int>::min(), "o", output));
		observers.push_back(std::make_unique<DummyObserver>(observable, -10, "l", output));
		observers.push_back(std::make_unique<DummyObserver>(observable, -5, "l", output));
		observers.push_back(std::make_unique<DummyObserver>(observable, 100, "e", output));
		observers.push_back(std::make_unique<DummyObserver>(observable, 1000, "h", output));

		BOOST_CHECK(output.is_empty());
		observable.SetData(20);
		BOOST_CHECK(output.is_equal("hello"));
	}
BOOST_AUTO_TEST_SUITE_END()
