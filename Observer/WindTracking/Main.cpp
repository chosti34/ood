#include "stdafx.h"
#include "WeatherStation.h"
#include "SimpleDisplay.h"
#include "StatisticsDisplay.h"

int main(int, char*[])
{
	InnerWeatherStation inner;
	OuterWeatherStation outer;

	SimpleDisplay simple(inner);
	StatisticsDisplayDuo advanced(inner, outer);

	inner.SetMeasurements({ 10, 0.5, 600 }); // будут оповещены SimpleDisplay, StatisticsDisplayDuo

	outer.SetMeasurements({ 12, 0.6, 700, 4, 90 }); // будет оповещен StatisticsDisplayDuo
	outer.SetMeasurements({ 15, 0.8, 800, 6, 15 }); // будет оповещен StatisticsDisplayDuo
	outer.SetMeasurements({ 15, 0.8, 800, 6, 15 }); // не будет оповещён никто, так как данные не изменились

	return 0;
}
