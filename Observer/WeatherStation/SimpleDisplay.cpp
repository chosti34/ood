#include "stdafx.h"
#include "SimpleDisplay.h"

void SimpleDisplay::Update(const WeatherInfo& data)
{
	std::cout << "Simple display update:" << std::endl;
	std::cout << "Current Temperature " << data.temperature << std::endl;
	std::cout << "Current Humidity " << data.humidity << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;
	std::cout << "----------------" << std::endl;
}
