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
	����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(const WeatherInfo& data) override
	{
		std::cout << "Current Temperature " << data.temperature << std::endl;
		std::cout << "Current Humidity " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

struct MinMax
{
	double min = std::numeric_limits<double>::infinity();
	double max = std::numeric_limits<double>::infinity();
	double accumulated;
};

class StatisticsDisplay : public IObserver<WeatherInfo>
{
private:
	void Update(const WeatherInfo& data) override
	{
		m_minTemperature = std::min(m_minTemperature, data.temperature);
		m_maxTemperature = std::max(m_maxTemperature, data.temperature);
		m_accumulatedTemperature += data.temperature;

		m_minHumidity = std::min(m_minHumidity, data.humidity);
		m_maxHumidity = std::max(m_maxHumidity, data.humidity);
		m_accumulatedHumidity += data.humidity;

		m_minPressure = std::min(m_minPressure, data.pressure);
		m_maxPressure = std::max(m_maxPressure, data.pressure);
		m_accumulatedPressure += data.pressure;

		++m_accumulationsCount;

		static const auto printStats = [&m_accumulationsCount](const std::string& statsName, const MinMax& stats) {
			std::cout << "Max " << statsName << ": " << stats.max << std::endl;
			std::cout << "Min " << statsName << ": " << stats.min << std::endl;
			std::cout << "Average Temperature " << (stats.accumulated / m_accumulationsCount) << std::endl;
		};

		

		std::cout << "Max Temperature: " << m_maxTemperature << std::endl;
		std::cout << "Min Temperature: " << m_minTemperature << std::endl;
		std::cout << "Average Temperature " << (m_accumulatedTemperature / m_accumulationsCount) << std::endl;

		std::cout << "Max Humidity: " << m_maxHumidity << std::endl;
		std::cout << "Min Humidity: " << m_minHumidity << std::endl;
		std::cout << "Average Humidity " << (m_accumulatedHumidity / m_accumulationsCount) << std::endl;

		std::cout << "Max Pressure: " << m_maxPressure << std::endl;
		std::cout << "Min Pressure: " << m_minPressure << std::endl;
		std::cout << "Average Pressure " << (m_accumulatedPressure / m_accumulationsCount) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	double m_minTemperature = std::numeric_limits<double>::infinity();
	double m_maxTemperature = -std::numeric_limits<double>::infinity();
	double m_accumulatedTemperature = 0;

	double m_minHumidity = std::numeric_limits<double>::infinity();
	double m_maxHumidity = -std::numeric_limits<double>::infinity();
	double m_accumulatedHumidity = 0;

	double m_minPressure = std::numeric_limits<double>::infinity();
	double m_maxPressure = -std::numeric_limits<double>::infinity();
	double m_accumulatedPressure = 0;

	unsigned m_accumulationsCount = 0;
};

class WeatherData : public AbstractObservable<WeatherInfo>
{
public:
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

protected:
	WeatherInfo GetChangedData()const override
	{
		return { m_temperature, m_humidity, m_pressure };
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
