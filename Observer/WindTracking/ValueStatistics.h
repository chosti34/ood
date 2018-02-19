#pragma once
#include <climits>
#include <cmath>

template <typename T>
class IValueStatistics
{
public:
	virtual void OnValueChange(T newValue) = 0;
	virtual T GetMinValue()const = 0;
	virtual T GetMaxValue()const = 0;
	virtual T GetAverage()const = 0;
};

template <typename T>
class SimpleStatistics : public IValueStatistics<T>
{
public:
	SimpleStatistics()
		: m_minValue(std::numeric_limits<T>::infinity())
		, m_maxValue(-std::numeric_limits<T>::infinity())
		, m_accumulated(T(0))
		, m_accumulationsCount(0u)
	{
	}

	void OnValueChange(T newValue)override
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

	T GetMinValue()const override
	{
		return m_minValue;
	}

	T GetMaxValue()const override
	{
		return m_maxValue;
	}

	T GetAverage()const override
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

// https://stackoverflow.com/questions/491738/how-do-you-calculate-the-average-of-a-set-of-circular-data
template <typename T>
class WindStatistics : public IValueStatistics<T>
{
public:
	WindStatistics()
		: m_minValue(std::numeric_limits<T>::infinity())
		, m_maxValue(-std::numeric_limits<T>::infinity())
		, m_x(0.0)
		, m_y(0.0)
		, m_accumulationsCount(0)
	{
	}

	void OnValueChange(T newValue)override
	{
		if (m_minValue > newValue)
		{
			m_minValue = newValue;
		}
		if (m_maxValue < newValue)
		{
			m_maxValue = newValue;
		}
		m_x += std::cos(newValue * 3.14159265 / 180.0);
		m_y += std::sin(newValue * 3.14159265 / 180.0);
		++m_accumulationsCount;
	}

	T GetMinValue()const override
	{
		return m_minValue;
	}

	T GetMaxValue()const override
	{
		return m_maxValue;
	}

	T GetAverage()const override
	{
		double ret = std::atan2(m_y / m_accumulationsCount, m_x / m_accumulationsCount) * 180.0 / 3.1459265;
		ret = round(ret);
		if (ret < -0.0)
		{
			ret = 360.0 + ret;
		}
		return std::fmod(ret, 360.0);
	}

private:
	double m_x;
	double m_y;
	double m_minValue;
	double m_maxValue;
	unsigned m_accumulationsCount;
};
