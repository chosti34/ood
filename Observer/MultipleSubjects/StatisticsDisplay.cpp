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

void PrintStatistics(const WeatherStatistics& statistics)
{
	PrintStatisticsValue(statistics.temperature, "Temperature");
	PrintStatisticsValue(statistics.humidity, "Humidity");
	PrintStatisticsValue(statistics.pressure, "Pressure");
	std::cout << "----------------" << std::endl;
}
}

StatisticsDisplay::StatisticsDisplay(WeatherData & innerStation, WeatherData & outerStation)
	: m_innerStation(innerStation)
	, m_outerStation(outerStation)
	, m_houseStatistics()
	, m_streetStatistics()
{
	m_innerStation.RegisterObserver(*this);
	m_outerStation.RegisterObserver(*this);
}

StatisticsDisplay::~StatisticsDisplay()
{
	m_innerStation.RemoveObserver(*this);
	m_outerStation.RemoveObserver(*this);
}

void StatisticsDisplay::Update(const WeatherInfo & data, IObservable<WeatherInfo>& observable)
{
	if (std::addressof(observable) == std::addressof(m_innerStation))
	{
		std::cout << "Notification from inner station" << std::endl;
		m_houseStatistics.temperature.OnValueChange(data.temperature);
		m_houseStatistics.humidity.OnValueChange(data.humidity);
		m_houseStatistics.pressure.OnValueChange(data.pressure);
		PrintStatistics(m_houseStatistics);
	}
	else if (std::addressof(observable) == std::addressof(m_outerStation))
	{
		std::cout << "Notification from outer station" << std::endl;
		m_streetStatistics.temperature.OnValueChange(data.temperature);
		m_streetStatistics.humidity.OnValueChange(data.humidity);
		m_streetStatistics.pressure.OnValueChange(data.pressure);
		PrintStatistics(m_streetStatistics);
	}
}
