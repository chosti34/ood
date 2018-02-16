#include "stdafx.h"
#include "WeatherData.h"

int main()
{
	WeatherData data;

	SimpleDisplay display1;
	data.RegisterObserver(display1, 100);

	StatisticsDisplay display2;
	data.RegisterObserver(display2, -1);

	data.SetMeasurements(100, 200, 300);
	data.RemoveObserver(display2);

	data.SetMeasurements(100, 100, 100);

	return 0;
}
