#include "stdafx.h"
#include "WeatherData.h"

void WeatherData::SetMeasurements(const WeatherInfo& info)
{
	bool temperatureOrPressureChanged =
		m_info.temperature != info.temperature ||
		m_info.pressure != info.pressure;

	bool anythingChanged =
		temperatureOrPressureChanged ||
		m_info.humidity != info.humidity ||
		m_info.windDirection != info.windDirection ||
		m_info.windSpeed != info.windSpeed;

	m_info = info;
	if (temperatureOrPressureChanged)
	{
		NotifyObservers(EventType::TemperatureOrPressureChange);
		NotifyObservers(EventType::AnyChange);
	}
	else if (anythingChanged)
	{
		NotifyObservers(EventType::AnyChange);
	}
}

WeatherInfo WeatherData::GetChangedData()const
{
	return m_info;
}
