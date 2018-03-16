#pragma once
#include <cassert>
#include "AbstractBeverage.h"
#include "BeverageTraits.h"

class Coffee : public AbstractBeverage
{
public:
	Coffee(const std::string& description = "Coffee")
		: AbstractBeverage(description)
	{
	}

	double GetCost()const
	{
		return 60.0;
	}
};

class Cappuccino : public Coffee
{
public:
	Cappuccino(CoffeePortionSize portionSize = CoffeePortionSize::Standard)
		: Coffee(ToString(portionSize) + "Cappuccino")
		, m_portionSize(portionSize)
	{
	}

	double GetCost()const
	{
		switch (m_portionSize)
		{
		case CoffeePortionSize::Standard:
			return 80.0;
		case CoffeePortionSize::Double:
			return 120.0;
		default:
			assert(false);
			throw std::logic_error("Cappuccino::GetCost(): default "
				"switch branch should be unreachable");
		}
	}

private:
	CoffeePortionSize m_portionSize;
};

class Latte : public Coffee
{
public:
	Latte(CoffeePortionSize portionSize = CoffeePortionSize::Standard)
		: Coffee(ToString(portionSize) + "Latte")
		, m_portionSize(portionSize)
	{
	}

	double GetCost()const override
	{
		switch (m_portionSize)
		{
		case CoffeePortionSize::Standard:
			return 90.0;
		case CoffeePortionSize::Double:
			return 130.0;
		default:
			assert(false);
			throw std::logic_error("Latte::GetCost(): default "
				"switch branch should be unreachable");
		}
	}

private:
	CoffeePortionSize m_portionSize;
};
