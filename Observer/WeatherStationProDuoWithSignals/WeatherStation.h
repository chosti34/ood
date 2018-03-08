#pragma once
#include "SignallingValue.h"
#include "WeatherInfo.h"

template <typename WeatherInfoType>
class WeatherStation
{
public:
	using WeatherSignal = boost::signals2::signal<void(const WeatherInfoType& newData)>;

	WeatherStation()
		: m_signallingValue()
	{
	}

	void SetMeasurements(const WeatherInfoType& measurements)
	{
		m_signallingValue = measurements;
	}

	boost::signals2::connection DoOnWeatherChange(typename const WeatherSignal::slot_type& slot)
	{
		return m_signallingValue.Connect1(slot, false);
	}

private:
	SignallingValue<WeatherInfoType> m_signallingValue;
};

using InnerWeatherStation = WeatherStation<WeatherInfo>;
using OuterWeatherStation = WeatherStation<WeatherInfoPro>;
