#include "stdafx.h"
#include "SimpleDisplay.h"

SimpleDisplay::SimpleDisplay(InnerWeatherStation& station)
	: m_station(station)
{
	m_station.RegisterObserver(WeatherEvent::TemperatureOrPressureChanged, *this);
}

SimpleDisplay::~SimpleDisplay()
{
	m_station.RemoveObserver(WeatherEvent::TemperatureOrPressureChanged, *this);
}

void SimpleDisplay::Update(const WeatherInfo& info, const IObservable<WeatherEvent, WeatherInfo>& observable)
{
	if (std::addressof(observable) == std::addressof(m_station))
	{
		std::cout << "SimpleDisplay - temperature or pressure changed:\n"
			<< "Temperature: " << info.temperature << "\n"
			<< "Humidity: " << info.humidity << "\n"
			<< "Pressure: " << info.pressure << "\n"
			<< "------------------" << std::endl;
	}
}
