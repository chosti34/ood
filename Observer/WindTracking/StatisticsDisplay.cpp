#include "stdafx.h"
#include "StatisticsDisplay.h"

namespace
{
void PrintStatistics(const IValueStatistics<double> & statistics, const std::string& name)
{
	std::cout << "Max " << name << ": " << statistics.GetMaxValue() << std::endl;
	std::cout << "Min " << name << ": " << statistics.GetMinValue() << std::endl;
	std::cout << "Average " << name << ": " << statistics.GetAverage() << std::endl;
}
}

StatisticsDisplay::StatisticsDisplay(WeatherData& innerStation, WeatherData& outerStation)
	: m_innerStation(innerStation)
	, m_outerStation(outerStation)
{
	m_innerStation.RegisterObserver(*this);
	m_outerStation.RegisterObserver(*this);
}

StatisticsDisplay::~StatisticsDisplay()
{
	m_innerStation.RemoveObserver(*this);
	m_outerStation.RemoveObserver(*this);
}

void StatisticsDisplay::Update(const WeatherInfoPro& data, IObservable<WeatherInfoPro>& observable)
{
	if (std::addressof(observable) == std::addressof(m_innerStation))
	{
		std::cout << "Notification from inner station" << std::endl;
	}
	else if (std::addressof(observable) == std::addressof(m_outerStation))
	{
		std::cout << "Notification from outer station" << std::endl;
	}

	m_temperatureStatistics.OnValueChange(data.temperature);
	m_humidityStatistics.OnValueChange(data.humidity);
	m_pressureStatistics.OnValueChange(data.pressure);
	m_windSpeedStatistics.OnValueChange(data.windSpeed);
	m_windDirectionStatistics.OnValueChange(data.windDirection);

	std::cout << "Statistics display update:" << std::endl;
	PrintStatistics(m_temperatureStatistics, "Temperature");
	PrintStatistics(m_humidityStatistics, "Humidity");
	PrintStatistics(m_pressureStatistics, "Pressure");
	PrintStatistics(m_windSpeedStatistics, "Wind Speed");
	PrintStatistics(m_windDirectionStatistics, "Wind Direction");
	std::cout << "----------------" << std::endl;
}
