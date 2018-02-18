#include "stdafx.h"
#include "WeatherData.h"

using namespace std::literals::string_literals;

void SimpleDisplay::Update(const WeatherInfo& data)
{
	std::cout << "Simple display update:" << std::endl;
	std::cout << "Current Temperature " << data.temperature << std::endl;
	std::cout << "Current Humidity " << data.humidity << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;
	std::cout << "----------------" << std::endl;
}

void StatisticsDisplay::PrintStatistics(const ValueStatistics<double>& statistics, const std::string& name)
{
	std::cout << "Max " << name << ": " << statistics.GetMaxValue() << std::endl;
	std::cout << "Min " << name << ": " << statistics.GetMinValue() << std::endl;
	std::cout << "Average " << name << ": " << statistics.GetAverage() << std::endl;
}

void StatisticsDisplay::Update(const WeatherInfo& data)
{
	m_temperatureStatistics.OnValueChange(data.temperature);
	m_humidityStatistics.OnValueChange(data.humidity);
	m_pressureStatistics.OnValueChange(data.pressure);

	std::cout << "Statistics display update:" << std::endl;
	PrintStatistics(m_temperatureStatistics, "Temperature"s);
	PrintStatistics(m_humidityStatistics, "Humidity"s);
	PrintStatistics(m_pressureStatistics, "Pressure"s);
	std::cout << "----------------" << std::endl;
}

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
