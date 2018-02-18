#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

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
	double GetTemperature()const; // Температура в градусах Цельсия
	double GetHumidity()const; // Относительная влажность (0...100)
	double GetPressure()const; // Атмосферное давление (в мм.рт.ст)

	void SetMeasurements(double temperature, double humidity, double pressure);

protected:
	WeatherInfo GetChangedData()const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
