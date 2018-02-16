#include "stdafx.h"
#include "../WeatherData.h"
#include <vector>
#include <string>

namespace
{
class MockSimpleDisplay : public SimpleDisplay
{
public:
	MockSimpleDisplay(std::vector<std::string>& signals)
		: m_signals(signals)
	{
	}

	void Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable)override
	{
		SimpleDisplay::Update(data, observable);
		m_signals.push_back(observable.GetDescription());
	}

private:
	std::vector<std::string> & m_signals;
};

class MockStatisticsDisplay : public StatisticsDisplay
{
public:
	MockStatisticsDisplay(std::vector<std::string>& signals)
		: m_signals(signals)
	{
	}

	void Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable)override
	{
		StatisticsDisplay::Update(data, observable);
		m_signals.push_back(observable.GetDescription());
	}

private:
	std::vector<std::string> & m_signals;
};
}

BOOST_AUTO_TEST_SUITE(MultipleSubjects)
	BOOST_AUTO_TEST_CASE(observers_can_distinguish_subjects_type_via_poll_model)
	{
		WeatherData wd1("in");
		WeatherData wd2("out");

		std::vector<std::string> signals;

		MockSimpleDisplay display1(signals);
		wd1.RegisterObserver(display1);
		wd2.RegisterObserver(display1);

		MockStatisticsDisplay display2(signals);
		wd1.RegisterObserver(display2);
		wd2.RegisterObserver(display2);

		BOOST_CHECK_EQUAL(signals.size(), 0u);
		wd1.SetMeasurements(10, 0.6, 600);
		BOOST_CHECK_EQUAL(signals.size(), 2u);
		BOOST_CHECK_EQUAL(signals[0], "in");
		BOOST_CHECK_EQUAL(signals[1], "in");

		wd2.SetMeasurements(15, 0.8, 700);
		BOOST_CHECK_EQUAL(signals.size(), 4u);
		BOOST_CHECK_EQUAL(signals[2], "out");
		BOOST_CHECK_EQUAL(signals[3], "out");
	}
BOOST_AUTO_TEST_SUITE_END()
