#include "stdafx.h"
#include "StatisticsDisplay.h"

StatisticsDisplay::StatisticsDisplay(WeatherData & innerStation, WeatherData & outerStation)
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

void StatisticsDisplay::Update(const WeatherInfo & data, IObservable<WeatherInfo>& observable)
{
	if (std::addressof(observable) == std::addressof(m_innerStation))
	{
		std::cout << "Notification from inner station" << std::endl;
	}
	else if (std::addressof(observable) == std::addressof(m_outerStation))
	{
		std::cout << "Notification from outer station" << std::endl;
	}

	if (m_minTemperature > data.temperature)
	{
		m_minTemperature = data.temperature;
	}
	if (m_maxTemperature < data.temperature)
	{
		m_maxTemperature = data.temperature;
	}
	m_accumulatedTemperature += data.temperature;
	++m_accumulationsCount;

	std::cout << "Max Temperature: " << m_maxTemperature << std::endl;
	std::cout << "Min Temperature: " << m_minTemperature << std::endl;
	std::cout << "Average Temperature " << (m_accumulatedTemperature / m_accumulationsCount) << std::endl;
	std::cout << "----------------" << std::endl;
}
