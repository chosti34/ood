#include "stdafx.h"
#include "WeatherData.h"

void WeatherData::SetMeasurements(const WeatherInfo& measurements)
{
	m_measurements = measurements;
	NotifyObservers();
}

WeatherInfo WeatherData::GetChangedData()const
{
	return m_measurements;
}
