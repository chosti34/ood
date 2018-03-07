#include "stdafx.h"
#include "StatisticsDisplay.h"

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	InnerWeatherStation inner;
	OuterWeatherStation outer;

	StatisticsDisplay display(inner, outer);
	inner.SetMeasurements(WeatherInfo(12, 0.5, 500));
	outer.SetMeasurements(WeatherInfoPro(15, 0.6, 700, 10, 10));

	inner.SetMeasurements(WeatherInfo(10, 0.4, 450));
	outer.SetMeasurements(WeatherInfoPro(10, 0.5, 800, 8, 100));

	return 0;
}
