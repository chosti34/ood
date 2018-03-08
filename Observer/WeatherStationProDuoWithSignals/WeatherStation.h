#pragma once
#include <boost/signals2.hpp>
#include <boost/noncopyable.hpp>

struct WeatherInfo
{
	double temperature = .0;
	double humidity = .0;
	double pressure = .0;
};

struct WeatherInfoPro
{
	double temperature = .0;
	double humidity = .0;
	double pressure = .0;
	double windSpeed = .0;
	double windDirection = .0;
};

template <typename WeatherInfoType>
class WeatherStation
{
public:
	using WeatherSignal = boost::signals2::signal<void(const WeatherInfoType& newData)>;

	void SetMeasurements(const WeatherInfoType& measurements)
	{
		m_measurements = measurements;
		m_signal(m_measurements);
	}

	boost::signals2::connection DoOnWeatherChange(typename const WeatherSignal::slot_type& slot)
	{
		return m_signal.connect(slot);
	}

private:
	WeatherInfoType m_measurements;
	WeatherSignal m_signal;
};

using InnerWeatherStation = WeatherStation<WeatherInfo>;
using OuterWeatherStation = WeatherStation<WeatherInfoPro>;
