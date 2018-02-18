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

void WeatherData::SetMeasurements(double temperature, double humidity, double pressure)
{
	m_temperature = temperature;
	m_humidity = humidity;
	m_pressure = pressure;
	NotifyObservers();
}

WeatherInfo WeatherData::GetChangedData()const
{
	return { m_temperature, m_humidity, m_pressure };
}
