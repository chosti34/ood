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
		lhs.pressure == rhs.pressure &&
		lhs.humidity == rhs.humidity;
}

inline bool operator !=(const WeatherInfo& lhs, const WeatherInfo& rhs)
{
	return !(lhs == rhs);
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
		lhs.pressure == rhs.pressure &&
		lhs.humidity == rhs.humidity &&
		lhs.windDirection == rhs.windDirection &&
		lhs.windSpeed == rhs.windSpeed;
}

inline bool operator !=(const WeatherInfoPro& lhs, const WeatherInfoPro& rhs)
{
	return !(lhs == rhs);
}
