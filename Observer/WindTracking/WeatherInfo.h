#pragma once

// TODO: fix code duplication
struct WeatherInfo
{
	double temperature = .0;
	double humidity = .0;
	double pressure = .0;
};

inline bool operator ==(const WeatherInfo& lhs, const WeatherInfo& rhs)
{
	return lhs.temperature == rhs.temperature && 
		lhs.humidity == rhs.humidity &&
		lhs.pressure == rhs.pressure;
}

inline bool operator !=(const WeatherInfo& lhs, const WeatherInfo& rhs)
{
	return !(lhs == rhs);
}

inline bool TemperatureOrPressureChanged(const WeatherInfo& oldData, const WeatherInfo& newData)
{
	return oldData.temperature != newData.temperature ||
		oldData.pressure != newData.pressure;
}

inline bool AnyParameterChanged(const WeatherInfo& oldData, const WeatherInfo& newData)
{
	return oldData != newData;
}

struct WeatherInfoPro
{
	double temperature = .0;
	double humidity = .0;
	double pressure = .0;
	double windSpeed = .0;
	double windDirection = .0;
};

inline bool operator ==(const WeatherInfoPro& lhs, const WeatherInfoPro& rhs)
{
	return lhs.temperature == rhs.temperature &&
		lhs.humidity == rhs.humidity &&
		lhs.pressure == rhs.pressure &&
		lhs.windSpeed == rhs.windSpeed &&
		lhs.windDirection == rhs.windDirection;
}

inline bool operator !=(const WeatherInfoPro& lhs, const WeatherInfoPro& rhs)
{
	return !(lhs == rhs);
}

inline bool TemperatureOrPressureChanged(const WeatherInfoPro& oldData, const WeatherInfoPro& newData)
{
	return oldData.temperature != newData.temperature ||
		oldData.pressure != newData.pressure;
}

inline bool AnyParameterChanged(const WeatherInfoPro& oldData, const WeatherInfoPro& newData)
{
	return oldData != newData;
}
