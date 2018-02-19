#include "stdafx.h"
#include "WeatherData.h"

void WeatherData::SetMeasurements(const WeatherInfo & info)
{
	m_info = info;
	NotifyObservers();
}

WeatherInfo WeatherData::GetChangedData()const
{
	return m_info;
}
