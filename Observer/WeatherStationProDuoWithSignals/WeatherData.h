#pragma once
#include "AbstractObservable.h"

struct WeatherInfo
{
	double temperature = 0.0;
	double humidity = 0.0;
	double pressure = 0.0;
	double windSpeed = 0.0;
	double windDirection = 0.0;
};

class WeatherData : public AbstractObservable<WeatherInfo>
{
public:
	void SetMeasurements(const WeatherInfo& measurements);

private:
	WeatherInfo GetChangedData()const override;

	WeatherInfo m_measurements;
};
