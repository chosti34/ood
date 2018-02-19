#pragma once
#include "WeatherData.h"
#include "ValueStatistics.h"

class StatisticsDisplay : public IObserver<WeatherInfoPro>
{
public:
	StatisticsDisplay(WeatherData& innerStation, WeatherData& outerStation);
	~StatisticsDisplay();

private:
	void Update(const WeatherInfoPro& data, IObservable<WeatherInfoPro>& observable) override;

	SimpleStatistics<double> m_temperatureStatistics;
	SimpleStatistics<double> m_humidityStatistics;
	SimpleStatistics<double> m_pressureStatistics;
	SimpleStatistics<double> m_windSpeedStatistics;
	WindStatistics<double> m_windDirectionStatistics;

	WeatherData& m_innerStation;
	WeatherData& m_outerStation;
};
