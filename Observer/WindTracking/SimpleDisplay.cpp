#include "stdafx.h"
#include "SimpleDisplay.h"

SimpleDisplay::SimpleDisplay(InnerWeatherStation& station)
	: m_station(station)
{
	m_station.RegisterObserver(EventType::AnyChange, *this);
}

SimpleDisplay::~SimpleDisplay()
{
	m_station.RemoveObserver(EventType::AnyChange, *this);
}

void SimpleDisplay::Update(const WeatherInfo& info, const IObservable<WeatherInfo>& observable)
{
	if (std::addressof(observable) == std::addressof(m_station))
	{
		std::cout << "SimpleDisplay: signal from inner weather station:\n"
			<< "Temperature: " << info.temperature << "\n"
			<< "Humidity: " << info.humidity << "\n"
			<< "Pressure: " << info.pressure << "\n"
			<< "------------------" << std::endl;
	}
}
