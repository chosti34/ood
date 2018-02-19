#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

#include "Observer.h"

struct WeatherInfo
{
	WeatherInfo(double temperature, double humidity, double pressure)
		: temperature(temperature)
		, humidity(humidity)
		, pressure(pressure)
	{
	}

	double temperature = 0.0;
	double humidity = 0.0;
	double pressure = 0.0;
};

struct WeatherInfoPro : public WeatherInfo
{
	WeatherInfoPro(double temperature, double humidity, double pressure,
		double windSpeed, double windDirection)
		: WeatherInfo(temperature, humidity, pressure)
		, windSpeed(windSpeed)
		, windDirection(windDirection)
	{
	}

	double windSpeed = 0.0;
	double windDirection = 0.0;
};

class WeatherData : public AbstractObservable<WeatherInfoPro>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const;

	// Относительная влажность (0...100)
	double GetHumidity()const;

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const;

	// Скорость ветра (в м/с)
	double GetWindSpeed()const;

	// Направление ветра (в градусах, где 0 - север, 90 - восток, 180 - юг, 270 - запад)
	double GetWindDirection()const;

	void SetMeasurements(double temperature, double humidity, double pressure,
		double windSpeed, double windDirection);

protected:
	WeatherInfoPro GetChangedData()const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 1.0;
	double m_windDirection = 0.0;
};
