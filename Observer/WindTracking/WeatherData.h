#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <optional>

#include "Observer.h"

struct WeatherInfo
{
	double temperature = .0;
	double humidity = .0;
	double pressure = .0;
};

struct WeatherInfoPro : public WeatherInfo
{
	double windSpeed = .0;
	std::optional<double> windDirection = .0;
};

class WeatherData : public AbstractObservable<WeatherInfo>
{
public:
	void SetMeasurements(const WeatherInfo& info);

private:
	WeatherInfo GetChangedData()const override;

	WeatherInfo m_info;
};
