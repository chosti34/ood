#include "stdafx.h"
#include "WeatherData.h"
#include "SimpleDisplay.h"
#include "StatisticsDisplay.h"

int main(int, char*[])
{
	WeatherData homeStation;
	WeatherData streetStation;

	StatisticsDisplay statisticsDisplay(homeStation, streetStation);
	homeStation.SetMeasurements({ 10, 0.4, 500 }); // не трогаем остальные поля
	streetStation.SetMeasurements({ 15, 0.6, 600, 30, 315 });

	return 0;
}
