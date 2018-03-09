#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

#include "Observer.h"
#include "WeatherInfo.h"

enum class WeatherEvent
{
	AnyParameterChanged,
	TemperatureOrPressureChanged // для рыбаков
};

template <typename WeatherInfoType>
inline std::set<WeatherEvent> GetEvents(const WeatherInfoType& oldData, const WeatherInfoType& newData)
{
	std::set<WeatherEvent> events;
	if (AnyParameterChanged(oldData, newData))
	{
		events.insert(WeatherEvent::AnyParameterChanged);
	}
	if (TemperatureOrPressureChanged(oldData, newData))
	{
		events.insert(WeatherEvent::TemperatureOrPressureChanged);
	}
	return events;
}

template <typename WeatherInfoType>
class WeatherStation : public AbstractObservable<WeatherEvent, WeatherInfoType>
{
public:
	void SetMeasurements(WeatherInfoType info)
	{
		std::swap(info, m_info);
		for (const auto& event : GetEvents(info, m_info))
		{
			// Приходиться писать имя базового класса здесь, так как компилятор
			//  не может найти метод NotifyObservers из-за использования шаблонного наследования
			AbstractObservable<WeatherEvent, WeatherInfoType>::NotifyObservers(event);
		}
	}

private:
	WeatherInfoType GetChangedData()const override
	{
		return m_info;
	}

	WeatherInfoType m_info;
};

using InnerWeatherStation = WeatherStation<WeatherInfo>;
using OuterWeatherStation = WeatherStation<WeatherInfoPro>;
