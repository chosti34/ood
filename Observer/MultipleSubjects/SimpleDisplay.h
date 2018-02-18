#pragma once
#include "WeatherData.h"

class SimpleDisplay : public IObserver<WeatherInfo>
{
public:
	SimpleDisplay(WeatherData& innerStation, WeatherData& outerStation);
	~SimpleDisplay();

private:
	void Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable) override;

	WeatherData & m_innerStation;
	WeatherData & m_outerStation;
};
