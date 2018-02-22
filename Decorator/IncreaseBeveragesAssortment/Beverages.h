#pragma once
#include "IBeverage.h"

class AbstractBeverage : public IBeverage
{
public:
	AbstractBeverage(const std::string& description)
		: m_description(description)
	{
	}

	std::string GetDescription()const override final
	{
		return m_description;
	}

private:
	std::string m_description;
};

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
	Cappuccino()
		: Coffee("Cappucino")
	{
	}

	double GetCost()const
	{
		return 80.0;
	}
};

class Latte : public Coffee
{
public:
	Latte()
		: Coffee("Latte")
	{
	}

	double GetCost()const override
	{
		return 90.0;
	}
};

class DoubleLatte : public AbstractBeverage
{
public:
	DoubleLatte()
		: AbstractBeverage("DoubleLatte")
	{
	}

	double GetCost()const override
	{
		return 130.0;
	}
};

class Tea : public AbstractBeverage
{
public:
	Tea()
		: AbstractBeverage("Tea")
	{
	}

	double GetCost()const override
	{
		return 30.0;
	}
};

class Milkshake : public AbstractBeverage
{
public:
	Milkshake()
		: AbstractBeverage("Milkshake")
	{
	}

	double GetCost()const override
	{
		return 80.0;
	}
};
