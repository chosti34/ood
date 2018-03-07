#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

#include "Observer.h"

enum class WeatherEvent
{
	AnythingChanged,
	TemperatureOrPressureChanged
};

struct WeatherInfo
{
	double temperature = 0.0;
	double humidity = 0.0;
	double pressure = 0.0;
};

// Намеренно не использовал наследование от WeatherInfo
struct WeatherInfoPro
{
	double temperature = 0.0;
	double humidity = 0.0;
	double pressure = 0.0;
	double windSpeed = 0.0;
	double windDirection = 0.0;
};

template <typename WeatherInfoType>
class WeatherStation : public AbstractObservable<WeatherEvent, WeatherInfoType>
{
	using Base = AbstractObservable<WeatherEvent, WeatherInfoType>;

public:
	virtual void SetMeasurements(const WeatherInfoType& info)
	{
		auto was = m_info;
		m_info = info;
		std::set<WeatherEvent> events = GetEvents(was, m_info);
		for (const auto& event : events)
		{
			Base::NotifyObservers(event);
		}
	}

protected:
	virtual std::set<WeatherEvent> GetEvents(const WeatherInfoType& was, const WeatherInfoType& now)const = 0;

private:
	WeatherInfoType GetChangedData()const override
	{
		return m_info;
	}

	WeatherInfoType m_info;
};

class InnerWeatherStation : public WeatherStation<WeatherInfo>
{
protected:
	std::set<WeatherEvent> GetEvents(const WeatherInfo& was, const WeatherInfo& now)const override
	{
		std::set<WeatherEvent> events;
		if (was.temperature == now.temperature &&
			was.pressure == now.pressure &&
			was.humidity == now.pressure)
		{
			return events;
		}
		events.insert(WeatherEvent::AnythingChanged);
		if (was.temperature != now.temperature ||
			was.pressure != now.pressure)
		{
			events.insert(WeatherEvent::TemperatureOrPressureChanged);
		}
		return events;
	}
};

class OuterWeatherStation : public WeatherStation<WeatherInfoPro>
{
protected:
	std::set<WeatherEvent> GetEvents(const WeatherInfoPro& was, const WeatherInfoPro& now)const override
	{
		std::set<WeatherEvent> events;
		if (was.temperature == now.temperature &&
			was.pressure == now.pressure &&
			was.humidity == now.humidity &&
			was.windDirection == now.windDirection &&
			was.windSpeed == now.windSpeed)
		{
			return events;
		}
		events.insert(WeatherEvent::AnythingChanged);
		if (was.temperature != now.temperature ||
			was.pressure != now.pressure)
		{
			events.insert(WeatherEvent::TemperatureOrPressureChanged);
		}
		return events;
	}
};
