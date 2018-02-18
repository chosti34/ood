#pragma once
#include "WeatherData.h"
#include <climits>

class StatisticsDisplay : public IObserver<WeatherInfo>
{
public:
	StatisticsDisplay(WeatherData& innerStation, WeatherData& outerStation);
	~StatisticsDisplay();

private:
	void Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable) override;

	double m_minTemperature = std::numeric_limits<double>::infinity();
	double m_maxTemperature = -std::numeric_limits<double>::infinity();
	double m_accumulatedTemperature = 0;
	unsigned m_accumulationsCount = 0;

	WeatherData & m_innerStation;
	WeatherData & m_outerStation;
};
