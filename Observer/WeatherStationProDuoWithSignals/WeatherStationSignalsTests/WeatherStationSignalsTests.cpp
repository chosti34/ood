#include "stdafx.h"
#include "../WeatherStation.h"
#include <boost/test/tools/output_test_stream.hpp>
#include <functional>

namespace
{
template <typename T>
class DummyObserver
{
public:
	DummyObserver(WeatherStation<T>& observable, boost::test_tools::output_test_stream& strm,
		const std::string& name)
		: m_strm(strm)
		, m_connection()
		, m_name(name)
		, m_unsubscribe(false)
	{
		m_connection = observable.DoOnWeatherChange(
			std::bind(&DummyObserver<T>::Update, this, std::placeholders::_1));
	}

	void Update(const T& data)
	{
		m_strm << m_name;
		if (m_unsubscribe && m_connection.connected())
		{
			m_connection.disconnect();
		}
	}

	void UnsubscribeOnNotification(bool unsubscribe)
	{
		m_unsubscribe = unsubscribe;
	}

	void Register(WeatherStation<T>& observable)
	{
		m_connection = observable.DoOnWeatherChange(
			std::bind(&DummyObserver<T>::Update, this, std::placeholders::_1));
	}

private:
	std::string m_name;
	boost::test_tools::output_test_stream& m_strm;
	boost::signals2::scoped_connection m_connection;
	bool m_unsubscribe;
};
}

BOOST_AUTO_TEST_SUITE(WeatherStationProDuoWithSignalsTaskTests)
	BOOST_AUTO_TEST_CASE(subscribers_are_notified_in_the_same_order_in_which_they_were_registered)
	{
		boost::test_tools::output_test_stream strm;
		WeatherStation<WeatherInfo> station;

		DummyObserver<WeatherInfo> obs1(station, strm, "h");
		DummyObserver<WeatherInfo> obs2(station, strm, "e");
		DummyObserver<WeatherInfo> obs3(station, strm, "l");
		DummyObserver<WeatherInfo> obs4(station, strm, "l");
		DummyObserver<WeatherInfo> obs5(station, strm, "o");

		station.SetMeasurements({ 30, 0.7, 600 });
		BOOST_CHECK(strm.is_equal("hello"));
	}

	BOOST_AUTO_TEST_CASE(subscribers_can_unregister_themselves_from_notifications_safely_in_update_method)
	{
		boost::test_tools::output_test_stream strm;
		WeatherStation<WeatherInfo> station;

		DummyObserver<WeatherInfo> observer1(station, strm, "a");
		observer1.UnsubscribeOnNotification(true);

		DummyObserver<WeatherInfo> observer2(station, strm, "b");

		station.SetMeasurements({ 15, 0.5, 800 });
		// Функции - слоты вызываются в том порядке, в котором они были зарегистрированы
		BOOST_CHECK(strm.is_equal("ab"));

		observer2.UnsubscribeOnNotification(true);
		station.SetMeasurements({ 10, 0.4, 900 });
		BOOST_CHECK(strm.is_equal("b"));

		station.SetMeasurements({ 20, 0.6, 700 });
		BOOST_CHECK(strm.is_empty());
	}

	BOOST_AUTO_TEST_CASE(subscribers_cannot_register_themselves_twice_or_more_times)
	{
		boost::test_tools::output_test_stream strm;

		WeatherStation<WeatherInfo> observable;
		DummyObserver<WeatherInfo> observer1(observable, strm, "a");
		DummyObserver<WeatherInfo> observer2(observable, strm, "b");

		observable.SetMeasurements({ 30, 0.5, 900 });
		BOOST_CHECK(strm.is_equal("ab"));

		observer1.Register(observable);
		observer2.Register(observable);

		observable.SetMeasurements({ 20, 0.6, 800 });
		BOOST_CHECK(strm.is_equal("ab"));
	}

	BOOST_AUTO_TEST_CASE(subscribers_can_register_themselves_again_after_unsubscribe)
	{
		boost::test_tools::output_test_stream strm;

		WeatherStation<WeatherInfo> observable;
		DummyObserver<WeatherInfo> observer1(observable, strm, "a");
		DummyObserver<WeatherInfo> observer2(observable, strm, "b");

		observer1.UnsubscribeOnNotification(true);
		observer2.UnsubscribeOnNotification(true);

		observable.SetMeasurements({ 30, 0.5, 900 });
		BOOST_CHECK(strm.is_equal("ab"));

		observable.SetMeasurements({ 40, 0.5, 800 });
		BOOST_CHECK(strm.is_empty());

		observer2.Register(observable);
		observer1.Register(observable);

		observable.SetMeasurements({ 10, 0.3, 700 });
		BOOST_CHECK(strm.is_equal("ba"));
	}
BOOST_AUTO_TEST_SUITE_END()
