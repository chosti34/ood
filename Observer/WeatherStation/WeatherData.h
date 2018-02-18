#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include "Observer.h"

struct WeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

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

template <typename T>
class ValueStatistics
{
public:
	ValueStatistics()
		: m_minValue(std::numeric_limits<T>::infinity())
		, m_maxValue(-std::numeric_limits<T>::infinity())
		, m_accumulated(T(0))
		, m_accumulationsCount(0u)
	{
	}

	void OnValueChange(T newValue)
	{
		if (newValue < m_minValue)
		{
			m_minValue = newValue;
		}
		if (newValue > m_maxValue)
		{
			m_maxValue = newValue;
		}
		m_accumulated += newValue;
		++m_accumulationsCount;
	}

	T GetMinValue()const
	{
		return m_minValue;
	}

	T GetMaxValue()const
	{
		return m_maxValue;
	}

	T GetAverage()const
	{
		// Если значение не было установлено ни разу, здесь будет деление на ноль
		return m_accumulated / m_accumulationsCount;
	}

private:
	T m_minValue;
	T m_maxValue;
	T m_accumulated;

	// Можно было бы хранить ссылку совместно со всеми объектами данного класса,
	//  чтобы сэкономить немного памяти (например: std::shared_ptr<unsigned>)
	unsigned m_accumulationsCount;
};

class StatisticsDisplay : public IObserver<WeatherInfo>
{
private:
	void PrintStatistics(const ValueStatistics<double>& statistics, const std::string& name);
	void Update(const WeatherInfo& data) override;

	ValueStatistics<double> m_temperatureStatistics;
	ValueStatistics<double> m_humidityStatistics;
	ValueStatistics<double> m_pressureStatistics;
};

class WeatherData : public AbstractObservable<WeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const;
	// Относительная влажность (0...100)
	double GetHumidity()const;
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const;
	void SetMeasurements(double temperature, double humidity, double pressure);

protected:
	WeatherInfo GetChangedData()const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
