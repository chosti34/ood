#pragma once
#include "Observer.h"
#include "WeatherData.h"
#include "ValueStatistics.h"

class StatisticsDisplay : public IObserver<WeatherInfo>
{
private:
	void PrintStatistics(const ValueStatistics<double>& statistics, const std::string& name);

	/*
	Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(const WeatherInfo& data) override;

	ValueStatistics<double> m_temperatureStatistics;
	ValueStatistics<double> m_humidityStatistics;
	ValueStatistics<double> m_pressureStatistics;
};
