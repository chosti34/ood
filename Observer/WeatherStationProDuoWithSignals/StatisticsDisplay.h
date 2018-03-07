#pragma once
#include "WeatherStation.h"
#include "ValueStatistics.h"

struct InnerWeatherStatistics
{
	SimpleStatistics<double> temperature;
	SimpleStatistics<double> humidity;
	SimpleStatistics<double> pressure;
};

struct OuterWeatherStatistics
{
	SimpleStatistics<double> temperature;
	SimpleStatistics<double> humidity;
	SimpleStatistics<double> pressure;
	SimpleStatistics<double> windSpeed;
	WindStatistics<double> windDirection;
};

class StatisticsDisplay
{
public:
	StatisticsDisplay(InnerWeatherStation& inner, OuterWeatherStation& outer);

private:
	void OnInnerWeatherInfoChange(const WeatherInfo& info);
	void OnOuterWeatherInfoChange(const WeatherInfoPro& info);

	boost::signals2::scoped_connection m_innerConnection;
	boost::signals2::scoped_connection m_outerConnection;

	InnerWeatherStatistics m_innerStatistics;
	OuterWeatherStatistics m_outerStatistics;
};
