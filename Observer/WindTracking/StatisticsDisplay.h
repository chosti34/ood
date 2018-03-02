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

class StatisticsDisplay
	: public IObserver<WeatherInfo>
	, public IObserver<WeatherInfoPro>
{
public:
	StatisticsDisplay(WeatherData& inner, WeatherData& outer);
	~StatisticsDisplay();

private:
	void Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable) override;
	void Update(const WeatherInfoPro& data, IObservable<WeatherInfoPro>& observable) override;

	HomeWeatherStatistics m_homeStatistics;
	StreetWeatherStatistics m_streetStatistics;

	WeatherData& m_inner;
	WeatherData& m_outer;
};
