#include "stdafx.h"
#include "SimpleDisplay.h"

//SimpleDisplay::SimpleDisplay(WeatherData & innerStation, WeatherData & outerStation)
//	: m_innerStation(innerStation)
//	, m_outerStation(outerStation)
//{
//	m_innerStation.RegisterObserver(*this);
//	m_outerStation.RegisterObserver(*this);
//}
//
//SimpleDisplay::~SimpleDisplay()
//{
//	m_innerStation.RemoveObserver(*this);
//	m_outerStation.RemoveObserver(*this);
//}
//
//void SimpleDisplay::Update(const WeatherInfoPro& data, IObservable<WeatherInfoPro>& observable)
//{
//	if (std::addressof(observable) == std::addressof(m_innerStation))
//	{
//		std::cout << "Notification from inner station" << std::endl;
//	}
//	else if (std::addressof(observable) == std::addressof(m_outerStation))
//	{
//		std::cout << "Notification from outer station" << std::endl;
//	}
//
//	std::cout << "Current Temperature " << data.temperature << std::endl;
//	std::cout << "Current Humidity " << data.humidity << std::endl;
//	std::cout << "Current Pressure " << data.pressure << std::endl;
//	std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
//	std::cout << "Current Wind Direction " << data.windDirection << std::endl;
//	std::cout << "----------------" << std::endl;
//}
