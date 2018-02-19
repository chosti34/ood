#include "stdafx.h"
#include "StatisticsDisplay.h"

namespace
{
void PrintStatisticsValue(const IValueStatistics<double> & statistics, const std::string& name)
{
	std::cout << "Max " << name << ": " << statistics.GetMaxValue() << std::endl;
	std::cout << "Min " << name << ": " << statistics.GetMinValue() << std::endl;
	std::cout << "Average " << name << ": " << statistics.GetAverage() << std::endl;
}

void PrintStatistics(const HomeWeatherStatistics& statistics)
{
	std::cout << "Signal from inner weather station:" << std::endl;
	PrintStatisticsValue(statistics.temperature, "Temperature");
	PrintStatisticsValue(statistics.humidity, "Humidity");
	PrintStatisticsValue(statistics.pressure, "Pressure");
	std::cout << "----------------" << std::endl;
}

void PrintStatistics(const StreetWeatherStatistics& statistics)
{
	std::cout << "Signal from outer weather station:" << std::endl;
	PrintStatisticsValue(statistics.temperature, "Temperature");
	PrintStatisticsValue(statistics.humidity, "Humidity");
	PrintStatisticsValue(statistics.pressure, "Pressure");
	PrintStatisticsValue(statistics.windSpeed, "Wind Speed");
	PrintStatisticsValue(statistics.windDirection, "Wind Direction");
	std::cout << "----------------" << std::endl;
}
}

StatisticsDisplay::StatisticsDisplay(WeatherData& inner, WeatherData& outer)
	: m_inner(inner)
	, m_outer(outer)
{
	m_inner.RegisterObserver(*this);
	m_outer.RegisterObserver(*this);
}

StatisticsDisplay::~StatisticsDisplay()
{
	m_inner.RemoveObserver(*this);
	m_outer.RemoveObserver(*this);
}

void StatisticsDisplay::Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable)
{
	if (std::addressof(observable) == std::addressof(m_inner))
	{
		// ��������������, ��� ������������, �������� �� ������� ������,
		//  �� ������������� ���������� � �������� � ����������� �����
		m_homeStatistics.temperature.OnValueChange(data.temperature);
		m_homeStatistics.humidity.OnValueChange(data.humidity);
		m_homeStatistics.pressure.OnValueChange(data.pressure);
		PrintStatistics(m_homeStatistics);
	}
	else if (std::addressof(observable) == std::addressof(m_outer))
	{
		m_streetStatistics.temperature.OnValueChange(data.temperature);
		m_streetStatistics.humidity.OnValueChange(data.humidity);
		m_streetStatistics.pressure.OnValueChange(data.pressure);
		m_streetStatistics.windSpeed.OnValueChange(data.windSpeed);
		m_streetStatistics.windDirection.OnValueChange(data.windDirection);
		PrintStatistics(m_streetStatistics);
	}
}
