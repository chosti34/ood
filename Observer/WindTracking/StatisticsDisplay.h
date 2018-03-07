#pragma once
#include "WeatherStation.h"
#include "ValueStatistics.h"

struct InnerWeatherStationStatistics
{
	SimpleStatistics<double> temperature;
	SimpleStatistics<double> humidity;
	SimpleStatistics<double> pressure;
};

struct OuterWeatherStationStatistics
{
	SimpleStatistics<double> temperature;
	SimpleStatistics<double> humidity;
	SimpleStatistics<double> pressure;
	SimpleStatistics<double> windSpeed;
	WindStatistics<double> windDirection;
};

// Дисплей, который следит сразу за двумя станциями и ведёт погодную статистику
class StatisticsDisplayDuo
	: public IObserver<WeatherInfo>
	, public IObserver<WeatherInfoPro>
{
public:
	StatisticsDisplayDuo(InnerWeatherStation& inner, OuterWeatherStation& outer);
	~StatisticsDisplayDuo();

private:
	void Update(const WeatherInfo& data, const IObservable<WeatherInfo>& observable) override;
	void Update(const WeatherInfoPro& data, const IObservable<WeatherInfoPro>& observable) override;

	InnerWeatherStationStatistics m_innerStatistics;
	OuterWeatherStationStatistics m_outerStatistics;

	InnerWeatherStation & m_inner;
	OuterWeatherStation & m_outer;
};
