#include "stdafx.h"
#include "StatisticsDisplay.h"
#include <functional>

namespace
{
void PrintStatisticsValue(const IValueStatistics<double>& statistics, const std::string& name)
{
	std::cout << "Max " << name << ": " << statistics.GetMaxValue() << std::endl;
	std::cout << "Min " << name << ": " << statistics.GetMinValue() << std::endl;
	std::cout << "Average " << name << ": " << statistics.GetAverage() << std::endl;
}

void PrintStatistics(const InnerWeatherStatistics& statistics)
{
	PrintStatisticsValue(statistics.temperature, "Temperature");
	PrintStatisticsValue(statistics.humidity, "Humidity");
	PrintStatisticsValue(statistics.pressure, "Pressure");
}

void PrintStatistics(const OuterWeatherStatistics& statistics)
{
	PrintStatisticsValue(statistics.temperature, "Temperature");
	PrintStatisticsValue(statistics.humidity, "Humidity");
	PrintStatisticsValue(statistics.pressure, "Pressure");
	PrintStatisticsValue(statistics.windSpeed, "Wind Speed");
	PrintStatisticsValue(statistics.windDirection, "Wind Direction");
}
}

StatisticsDisplay::StatisticsDisplay(InnerWeatherStation& inner, OuterWeatherStation& outer)
{
	m_innerConnection = inner.DoOnWeatherChange(
		std::bind(&StatisticsDisplay::OnInnerWeatherInfoChange, this, std::placeholders::_1));
	m_outerConnection = outer.DoOnWeatherChange(
		std::bind(&StatisticsDisplay::OnOuterWeatherInfoChange, this, std::placeholders::_1));
}

void StatisticsDisplay::OnInnerWeatherInfoChange(const WeatherInfo& info)
{
	m_innerStatistics.temperature.Accumulate(info.temperature);
	m_innerStatistics.humidity.Accumulate(info.humidity);
	m_innerStatistics.pressure.Accumulate(info.pressure);
	std::cout << "Signal from inner weather station:" << std::endl;
	PrintStatistics(m_innerStatistics);
	std::cout << "----------------" << std::endl;
}

void StatisticsDisplay::OnOuterWeatherInfoChange(const WeatherInfoPro& info)
{
	m_outerStatistics.temperature.Accumulate(info.temperature);
	m_outerStatistics.humidity.Accumulate(info.humidity);
	m_outerStatistics.pressure.Accumulate(info.pressure);
	m_outerStatistics.windDirection.Accumulate(info.windDirection);
	m_outerStatistics.windSpeed.Accumulate(info.windSpeed);
	std::cout << "Signal from outer weather station:" << std::endl;
	PrintStatistics(m_outerStatistics);
	std::cout << "----------------" << std::endl;
}
