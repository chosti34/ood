#pragma once
#include "WeatherData.h"
#include "ValueStatistics.h"
#include <climits>

struct WeatherStatistics
{
	SimpleStatistics<double> temperature;
	SimpleStatistics<double> humidity;
	SimpleStatistics<double> pressure;
};

class StatisticsDisplay : public IObserver<WeatherInfo>
{
public:
	StatisticsDisplay(WeatherData& innerStation, WeatherData& outerStation);
	~StatisticsDisplay();

private:
	void Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable) override;

	WeatherStatistics m_houseStatistics;
	WeatherStatistics m_streetStatistics;

	WeatherData & m_innerStation;
	WeatherData & m_outerStation;
};
