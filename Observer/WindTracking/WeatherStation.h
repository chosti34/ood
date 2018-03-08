#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

#include "Observer.h"

enum class WeatherEvent
{
	AnythingChanged,
	TemperatureOrPressureChanged,
	WindDirectionChanged
};

struct WeatherInfo
{
	WeatherInfo(
		double temperature = .0,
		double humidity = .0,
		double pressure = .0)
		: temperature(temperature)
		, humidity(humidity)
		, pressure(pressure)
	{
	}

	double temperature;
	double humidity;
	double pressure;
};

// Можно было обойтись без наследования
struct WeatherInfoPro : WeatherInfo
{
	WeatherInfoPro(
		double temperature = .0,
		double humidity = .0,
		double pressure = .0,
		double windSpeed = .0,
		double windDirection = .0)
		: WeatherInfo(temperature, humidity, pressure)
		, windSpeed(windSpeed)
		, windDirection(windDirection)
	{
	}

	double windSpeed;
	double windDirection;
};

inline std::set<WeatherEvent> GetWeatherInfoEvents(const WeatherInfo& oldData, const WeatherInfo& newData)
{
	std::set<WeatherEvent> changes;
	// Если не произошло никаких изменений в данных, возвращаем пустое множество
	if (oldData.temperature == newData.temperature &&
		oldData.humidity == newData.humidity &&
		oldData.pressure == newData.pressure)
	{
		return changes;
	}
	// Что-то всё-таки произошло
	changes.insert(WeatherEvent::AnythingChanged);
	if (oldData.temperature != newData.temperature ||
		oldData.pressure != newData.pressure)
	{
		// Изменились температура либо атмосферное давление
		changes.insert(WeatherEvent::TemperatureOrPressureChanged);
	}
	return changes;
}

inline std::set<WeatherEvent> GetWeatherInfoEvents(const WeatherInfoPro& oldData, const WeatherInfoPro& newData)
{
	auto changes = GetWeatherInfoEvents(static_cast<WeatherInfo>(oldData), static_cast<WeatherInfo>(newData));
	if (oldData.windDirection == newData.windDirection &&
		oldData.windSpeed == newData.windSpeed)
	{
		// Данные о ветре не изменились
		return changes;
	}
	if (oldData.windDirection != newData.windDirection ||
		oldData.windSpeed != newData.windSpeed)
	{
		// Функция обрабатывающая базовую WeatherInfo могла и не вернуть
		//  WeatherEvent::AnythingChanged, однако данные о ветре изменились
		changes.insert(WeatherEvent::AnythingChanged);
	}
	if (oldData.windDirection != newData.windDirection)
	{
		changes.insert(WeatherEvent::WindDirectionChanged);
	}
	return changes;
}

template <typename WeatherInfoType>
class WeatherStation : public AbstractObservable<WeatherEvent, WeatherInfoType>
{
public:
	void SetMeasurements(const WeatherInfoType& info)
	{
		auto oldData = m_info;
		m_info = info;
		for (const auto& event : GetWeatherInfoEvents(oldData, m_info))
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
