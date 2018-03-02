#include "stdafx.h"
#include "StatisticsDisplay.h"

void StatisticsDisplay::PrintStatistics(const ValueStatistics<double>& statistics, const std::string& name)
{
	std::cout << "Max " << name << ": " << statistics.GetMaxValue() << std::endl;
	std::cout << "Min " << name << ": " << statistics.GetMinValue() << std::endl;
	std::cout << "Average " << name << ": " << statistics.GetAverage() << std::endl;
}

void StatisticsDisplay::Update(const WeatherInfo& data)
{
	m_temperatureStatistics.Accumulate(data.temperature);
	m_humidityStatistics.Accumulate(data.humidity);
	m_pressureStatistics.Accumulate(data.pressure);

	std::cout << "Statistics display update:" << std::endl;
	PrintStatistics(m_temperatureStatistics, "Temperature");
	PrintStatistics(m_humidityStatistics, "Humidity");
	PrintStatistics(m_pressureStatistics, "Pressure");
	std::cout << "----------------" << std::endl;
}
