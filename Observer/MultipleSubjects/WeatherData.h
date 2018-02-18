#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

#include "Observer.h"

struct WeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class WeatherData : public AbstractObservable<WeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const;

	// Относительная влажность (0...100)
	double GetHumidity()const;

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const;

	void SetMeasurements(double temperature, double humidity, double pressure);

protected:
	WeatherInfo GetChangedData()const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
