#pragma once
#include "WeatherData.h"

class SimpleDisplay : public IObserver<WeatherInfo>
{
public:
	SimpleDisplay();
	~SimpleDisplay();

private:
	void Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable) override;
};
