#pragma once
#include <climits>

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

	void Accumulate(const T& newValue)
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
