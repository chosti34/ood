#include "stdafx.h"
#include "StatisticsDisplay.h"

namespace
{
void PrintStatisticsValue(const IValueStatistics<double>& statistics, const std::string& name)
{
	std::cout << "Max " << name << ": " << statistics.GetMaxValue() << std::endl;
	std::cout << "Min " << name << ": " << statistics.GetMinValue() << std::endl;
	std::cout << "Average " << name << ": " << statistics.GetAverage() << std::endl;
}

void PrintStatistics(const InnerWeatherStationStatistics& statistics)
{
	PrintStatisticsValue(statistics.temperature, "Temperature");
	PrintStatisticsValue(statistics.humidity, "Humidity");
	PrintStatisticsValue(statistics.pressure, "Pressure");
}

void PrintStatistics(const OuterWeatherStationStatistics& statistics)
{
	PrintStatisticsValue(statistics.temperature, "Temperature");
	PrintStatisticsValue(statistics.humidity, "Humidity");
	PrintStatisticsValue(statistics.pressure, "Pressure");
	PrintStatisticsValue(statistics.windSpeed, "Wind Speed");
	PrintStatisticsValue(statistics.windDirection, "Wind Direction");
}
}

StatisticsDisplayDuo::StatisticsDisplayDuo(InnerWeatherStation& inner, OuterWeatherStation& outer)
	: m_inner(inner)
	, m_outer(outer)
{
	m_inner.RegisterObserver(WeatherEvent::AnythingChanged, *this);
	m_outer.RegisterObserver(WeatherEvent::AnythingChanged, *this);
}

StatisticsDisplayDuo::~StatisticsDisplayDuo()
{
	m_inner.RemoveObserver(WeatherEvent::AnythingChanged, *this);
	m_outer.RemoveObserver(WeatherEvent::AnythingChanged, *this);
}

void StatisticsDisplayDuo::Update(const WeatherInfo& data, const IObservable<WeatherEvent, WeatherInfo>& observable)
{
	if (std::addressof(observable) == std::addressof(m_inner))
	{
		m_innerStatistics.temperature.Accumulate(data.temperature);
		m_innerStatistics.humidity.Accumulate(data.humidity);
		m_innerStatistics.pressure.Accumulate(data.pressure);
		std::cout << "StatisticsDisplayDuo - signal from inner weather station\n";
		PrintStatistics(m_innerStatistics);
		std::cout << "------------------" << std::endl;
	}
}

void StatisticsDisplayDuo::Update(const WeatherInfoPro& data, const IObservable<WeatherEvent, WeatherInfoPro>& observable)
{
	if (std::addressof(observable) == std::addressof(m_outer))
	{
		m_outerStatistics.temperature.Accumulate(data.temperature);
		m_outerStatistics.humidity.Accumulate(data.humidity);
		m_outerStatistics.pressure.Accumulate(data.pressure);
		m_outerStatistics.windDirection.Accumulate(data.windDirection);
		m_outerStatistics.windSpeed.Accumulate(data.windSpeed);
		std::cout << "StatisticsDisplayDuo - signal from outer weather station\n";
		PrintStatistics(m_outerStatistics);
		std::cout << "------------------" << std::endl;
	}
}
