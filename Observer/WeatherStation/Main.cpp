#include "stdafx.h"
#include "WeatherData.h"

int main(int /* argc */, char* /* argv */[])
{
	WeatherData weatherData;

	SimpleDisplay simpleDisplay;
	weatherData.RegisterObserver(simpleDisplay);

	StatisticsDisplay statisticsDisplay;
	weatherData.RegisterObserver(statisticsDisplay);

	weatherData.SetMeasurements(3, 0.7, 760);
	weatherData.SetMeasurements(4, 0.8, 761);

	weatherData.RemoveObserver(statisticsDisplay);

	weatherData.SetMeasurements(10, 0.8, 761);
	weatherData.SetMeasurements(-10, 0.8, 761);

	return 0;
}
