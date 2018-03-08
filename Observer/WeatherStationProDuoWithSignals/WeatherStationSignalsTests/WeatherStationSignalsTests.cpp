#include "stdafx.h"
#include "../WeatherStation.h"
#include <boost/test/tools/output_test_stream.hpp>

namespace
{
class DummyObserver
{
public:
	DummyObserver(boost::test_tools::output_test_stream& strm)
		: m_strm(strm)
		, m_connection()
	{
	}

	void Update(const WeatherInfo& data)
	{
	}

	void UnsubscribeOnNotification()
	{
	}

private:
	boost::test_tools::output_test_stream& m_strm;
	boost::signals2::scoped_connection m_connection;
};
}

BOOST_AUTO_TEST_SUITE(WeatherStationProDuoWithSignalsTaskTests)
	BOOST_AUTO_TEST_CASE(subscribers_can_unregister_themselves_from_notifications_safely_in_update_method)
	{
		boost::test_tools::output_test_stream strm;

		WeatherData observable;
		DummyObserver observer1(observable, strm, true, "a");
		DummyObserver observer2(observable, strm, false, "b");

		observable.SetMeasurements({ 15, 0.5, 800 });
		// Функции - слоты вызываются в том порядке, в котором они были зарегистрированы
		BOOST_CHECK(strm.is_equal("ab", true));

		observer2.SetErase(true);
		observable.SetMeasurements({ 10, 0.4, 900 });
		BOOST_CHECK(strm.is_equal("b"));

		observable.SetMeasurements({ 20, 0.6, 700 });
		BOOST_CHECK(strm.is_empty());
	}

	BOOST_AUTO_TEST_CASE(subscribers_cannot_register_to_notifiers_twice_or_more_times)
	{
		boost::test_tools::output_test_stream strm;

		WeatherData observable;
		DummyObserver observer1(observable, strm, false, "a");
		DummyObserver observer2(observable, strm, false, "b");

		boost::signals2::scoped_connection connection1;
		boost::signals2::scoped_connection connection2;

		BOOST_CHECK(!observable.RegisterObserver(observer1, connection1));
		BOOST_CHECK(!observable.RegisterObserver(observer2, connection2));

		observable.SetMeasurements({ 30, 0.5, 900 });
		BOOST_CHECK(strm.is_equal("ab"));
	}

	BOOST_AUTO_TEST_CASE(subscribers_can_resubscribe)
	{
		boost::test_tools::output_test_stream strm;

		WeatherData observable;
		DummyObserver observer1(observable, strm, false, "a");
		DummyObserver observer2(observable, strm, false, "b");

		observable.SetMeasurements({ 30, 0.5, 900 });
		BOOST_CHECK(strm.is_equal("ab"));

		observable.RemoveObserver(observer1);
		observable.SetMeasurements({ 40, 0.5, 800 });
		BOOST_CHECK(strm.is_equal("b"));

		boost::signals2::scoped_connection connection1;

		BOOST_CHECK(observable.RegisterObserver(observer1, connection1));
		observable.SetMeasurements({ 10, 0.3, 700 });
		BOOST_CHECK(strm.is_equal("ba"));
	}
BOOST_AUTO_TEST_SUITE_END()
