#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

#include "Observer.h"

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

template <typename T>
class WeatherStation : public AbstractObservable<T>
{
	using Observable = AbstractObservable<T>;

public:
	void SetMeasurements(const T& info)
	{
		m_info = info;
		// Компилятору нужно конкретизировать: от класса с каким шаблонным параметром
		//  мы унаследовались
		Observable::NotifyObservers(EventType::AnyChange);
	}

private:
	T GetChangedData()const override
	{
		return m_info;
	}

	T m_info;
};

using InnerWeatherStation = WeatherStation<WeatherInfo>;
using OuterWeatherStation = WeatherStation<WeatherInfoPro>;
