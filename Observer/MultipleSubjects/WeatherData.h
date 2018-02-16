#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct WeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class WeatherData : public AbstractObservable<WeatherInfo>
{
public:
	WeatherData(const std::string& description)
		: m_description(description)
	{
	}

	// ����������� � �������� �������
	double GetTemperature()const
	{
		return m_temperature;
	}

	// ������������� ��������� (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}

	// ����������� �������� (� ��.��.��)
	double GetPressure()const
	{
		return m_pressure;
	}

	void SetMeasurements(double temperature, double humidity, double pressure)
	{
		m_temperature = temperature;
		m_humidity = humidity;
		m_pressure = pressure;
		NotifyObservers();
	}

	std::string GetDescription()const override
	{
		return m_description;
	}

protected:
	WeatherInfo GetChangedData()const override
	{
		return { m_temperature, m_humidity, m_pressure };
	}

private:
	std::string m_description;
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

class SimpleDisplay : public IObserver<WeatherInfo>
{
protected:
	void Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable) override
	{
		std::cout << "Notify from " << observable.GetDescription() << " subject:" << std::endl;
		std::cout << "Current Temperature " << data.temperature << std::endl;
		std::cout << "Current Humidity " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class StatisticsDisplay : public IObserver<WeatherInfo>
{
protected:
	void Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable) override
	{
		if (m_minTemperature > data.temperature)
		{
			m_minTemperature = data.temperature;
		}
		if (m_maxTemperature < data.temperature)
		{
			m_maxTemperature = data.temperature;
		}
		m_accumulatedTemperature += data.temperature;
		++m_accumulationsCount;

		std::cout << "Notify from " << observable.GetDescription() << " subject:" << std::endl;
		std::cout << "Max Temperature: " << m_maxTemperature << std::endl;
		std::cout << "Min Temperature: " << m_minTemperature << std::endl;
		std::cout << "Average Temperature " << (m_accumulatedTemperature / m_accumulationsCount) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	double m_minTemperature = std::numeric_limits<double>::infinity();
	double m_maxTemperature = -std::numeric_limits<double>::infinity();
	double m_accumulatedTemperature = 0;
	unsigned m_accumulationsCount = 0;
};
