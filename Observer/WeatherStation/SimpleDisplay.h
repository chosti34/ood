#pragma once
#include "Observer.h"
#include "WeatherData.h"

class SimpleDisplay : public IObserver<WeatherInfo>
{
private:
	/*
	Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(const WeatherInfo& data) override;
};
