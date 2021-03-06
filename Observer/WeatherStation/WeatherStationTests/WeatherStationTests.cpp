#include "stdafx.h"
#include "../ValueStatistics.h"
#include "../WeatherData.h"

namespace
{
class SavingWeatherInfoObserver : public IObserver<WeatherInfo>
{
public:
	WeatherInfo GetWeatherInfo()const
	{
		return m_weatherInfo;
	}

private:
	void Update(const WeatherInfo& data) override
	{
		m_weatherInfo = data;
	}

	WeatherInfo m_weatherInfo;
};

bool IsEqual(double lhs, double rhs)
{
	return std::abs(lhs - rhs) < DBL_EPSILON;
}

bool WeatherInfoEquals(const WeatherInfo& lhs, const WeatherInfo& rhs)
{
	return IsEqual(lhs.temperature, rhs.temperature) &&
		IsEqual(lhs.pressure, rhs.pressure) &&
		IsEqual(lhs.humidity, rhs.humidity);
}
}

BOOST_AUTO_TEST_SUITE(WeatherStationStatisticsTaskTestSuite)
	BOOST_AUTO_TEST_SUITE(helper_statistics_class)
		BOOST_AUTO_TEST_CASE(can_measure_statistics_correctly)
		{
			ValueStatistics<double> statistics;

			statistics.Accumulate(10.0);
			statistics.Accumulate(15.0);
			statistics.Accumulate(20.0);

			BOOST_CHECK(IsEqual(statistics.GetMinValue(), 10.0));
			BOOST_CHECK(IsEqual(statistics.GetMaxValue(), 20.0));
			BOOST_CHECK(IsEqual(statistics.GetAverage(), 15.0));
		}

		BOOST_AUTO_TEST_CASE(have_very_big_and_very_small_min_max_initial_values)
		{
			ValueStatistics<int> statistics;
			BOOST_CHECK_EQUAL(statistics.GetMinValue(), std::numeric_limits<int>::infinity());
			BOOST_CHECK_EQUAL(statistics.GetMaxValue(), -std::numeric_limits<int>::infinity());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(observers_notified_on_measurements_set)
	{
		WeatherData weatherData;

		SavingWeatherInfoObserver saver;
		weatherData.RegisterObserver(saver);

		WeatherInfo info = { 8, 0.6, 700 };
		weatherData.SetMeasurements(info.temperature, info.humidity, info.pressure);

		BOOST_CHECK(WeatherInfoEquals(info, saver.GetWeatherInfo()));
	}
BOOST_AUTO_TEST_SUITE_END()
