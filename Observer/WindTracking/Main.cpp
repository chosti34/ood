#include "stdafx.h"
#include "WeatherData.h"
#include "SimpleDisplay.h"
#include "StatisticsDisplay.h"

int main(int, char*[])
{
	WeatherData inner;
	WeatherData outer;

	{
		SimpleDisplay simpleDisplay(inner, outer);
		inner.SetMeasurements(10, 0.4, 800, 20, 90);
	}

	StatisticsDisplay statisticsDisplay(inner, outer);
	inner.SetMeasurements(10, 0.4, 500, 20, 315);
	inner.SetMeasurements(15, 0.6, 600, 30, 45);

	return 0;
}
