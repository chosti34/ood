#include "stdafx.h"
#include "WeatherData.h"

double WeatherData::GetTemperature()const
{
	return m_temperature;
}

double WeatherData::GetHumidity()const
{
	return m_humidity;
}

double WeatherData::GetPressure()const
{
	return m_pressure;
}

double WeatherData::GetWindSpeed() const
{
	return m_windSpeed;
}

double WeatherData::GetWindDirection() const
{
	return m_windDirection;
}

void WeatherData::SetMeasurements(double temperature, double humidity, double pressure,
	double windSpeed, double windDirection)
{
	m_temperature = temperature;
	m_humidity = humidity;
	m_pressure = pressure;
	m_windSpeed = windSpeed;
	m_windDirection = windDirection;
	NotifyObservers();
}

WeatherInfoPro WeatherData::GetChangedData()const
{
	return { m_temperature, m_humidity, m_pressure, m_windSpeed, m_windDirection };
}
