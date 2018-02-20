#pragma once
#include "WeatherData.h"
#include "ValueStatistics.h"

struct HomeWeatherStatistics
{
	SimpleStatistics<double> temperature;
	SimpleStatistics<double> humidity;
	SimpleStatistics<double> pressure;
};

struct StreetWeatherStatistics
{
	SimpleStatistics<double> temperature;
	SimpleStatistics<double> humidity;
	SimpleStatistics<double> pressure;
	SimpleStatistics<double> windSpeed;
	WindStatistics<double> windDirection;
};

class StatisticsDisplay : public IObserver<WeatherInfo>
{
public:
	StatisticsDisplay(WeatherData& inner, WeatherData& outer);
	void Update(const WeatherInfo& data, const IObservable<WeatherInfo>& observable) override;

private:
	WeatherData & m_inner;
	WeatherData & m_outer;

	HomeWeatherStatistics m_homeStatistics;
	StreetWeatherStatistics m_streetStatistics;

	boost::signals2::scoped_connection m_inConnection;
	boost::signals2::scoped_connection m_outConnection;
};
