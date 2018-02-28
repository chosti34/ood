#pragma once
#include <cassert>
#include <algorithm>
#include "IBeverage.h"

// Базовый декоратор "Добавка к напитку". Также является напитком.
class AbstractCondimentDecorator : public IBeverage
{
public:
	std::string GetDescription()const override
	{
		// Описание декорированного напитка добавляется к описанию оборачиваемого напитка
		return m_beverage->GetDescription() + ", " + GetCondimentDescription();
	}

	double GetCost()const override
	{
		// Стоимость складывается из стоимости добавки и стоимости оборачиваемого напитка
		return m_beverage->GetCost() + GetCondimentCost();
	}

protected:
	AbstractCondimentDecorator(IBeveragePtr&& beverage)
		: m_beverage(std::move(beverage))
	{
	}

	// Стоимость и описание добавки вычисляется в классах конкретных декораторов
	virtual std::string GetCondimentDescription()const = 0;
	virtual double GetCondimentCost()const = 0;

private:
	IBeveragePtr m_beverage;
};

// Добавка из корицы
class CinnamonCondiment : public AbstractCondimentDecorator
{
public:
	CinnamonCondiment(IBeveragePtr&& beverage)
		: AbstractCondimentDecorator(std::move(beverage))
	{
	}

protected:
	double GetCondimentCost()const override
	{
		return 20.0;
	}

	std::string GetCondimentDescription()const override
	{
		return "Cinnamon";
	}
};

// Лимонная добавка
class LemonCondiment : public AbstractCondimentDecorator
{
public:
	LemonCondiment(IBeveragePtr&& beverage, unsigned quantity = 1)
		: AbstractCondimentDecorator(std::move(beverage))
		, m_quantity(quantity)
	{
	}

protected:
	double GetCondimentCost()const override
	{
		return 10.0 * m_quantity;
	}

	std::string GetCondimentDescription()const override
	{
		return "Lemon x" + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
};

enum class IceCubeType
{
	Dry,	// Сухой лёд (для суровых сибирских мужиков)
	Water	// Обычные кубики из воды
};

// Добавка "Кубики льда". Определяется типом и количеством кубиков, что
//  влияет на стоимость и описание
class IceCubesCondiment : public AbstractCondimentDecorator
{
public:
	IceCubesCondiment(IBeveragePtr&& beverage, unsigned quantity, IceCubeType type = IceCubeType::Water)
		: AbstractCondimentDecorator(std::move(beverage))
		, m_quantity(quantity)
		, m_type(type)
	{
	}

protected:
	double GetCondimentCost()const override
	{
		return (m_type == IceCubeType::Dry ? 10.0 : 5.0) * m_quantity;
	}

	std::string GetCondimentDescription()const override
	{
		return std::string(m_type == IceCubeType::Dry ? "Dry" : "Water")
			+ " ice cubes x" + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
	IceCubeType m_type;
};

enum class SyrupType
{
	Chocolate,
	Maple
};

class SyrupCondiment : public AbstractCondimentDecorator
{
public:
	SyrupCondiment(IBeveragePtr&& beverage, SyrupType type)
		: AbstractCondimentDecorator(std::move(beverage))
		, m_type(type)
	{
	}

protected:
	double GetCondimentCost()const override
	{
		return 15.0;
	}

	std::string GetCondimentDescription()const override
	{
		return std::string(m_type == SyrupType::Chocolate ? "Chocolate" : "Maple")
			+ " syrup";
	}

private:
	SyrupType m_type;
};

// Шоколадная стружка
class ChocolateCrumbsCondiment : public AbstractCondimentDecorator
{
public:
	ChocolateCrumbsCondiment(IBeveragePtr&& beverage, unsigned mass)
		: AbstractCondimentDecorator(std::move(beverage))
		, m_mass(mass)
	{
	}

protected:
	double GetCondimentCost()const override
	{
		return 2 * m_mass;
	}

	std::string GetCondimentDescription()const override
	{
		return "Chocolate crumbs " + std::to_string(m_mass) + "g";
	}

private:
	unsigned m_mass;
};

// Кокосовая стружка
class CoconutFlakesCondiment : public AbstractCondimentDecorator
{
public:
	CoconutFlakesCondiment(IBeveragePtr&& beverage, unsigned mass)
		: AbstractCondimentDecorator(std::move(beverage))
		, m_mass(mass)
	{
	}

protected:
	double GetCondimentCost()const override
	{
		return m_mass;
	}

	std::string GetCondimentDescription()const override
	{
		return "Cuconut flakes " + std::to_string(m_mass) + "g";
	}

private:
	unsigned m_mass;
};

class CreamCondiment : public AbstractCondimentDecorator
{
public:
	CreamCondiment(IBeveragePtr&& beverage)
		: AbstractCondimentDecorator(std::move(beverage))
	{
	}

protected:
	std::string GetCondimentDescription()const override
	{
		return "Cream";
	}

	double GetCondimentCost()const override
	{
		return 25.0;
	}
};

class ChocolateSlicesCondiment : public AbstractCondimentDecorator
{
public:
	ChocolateSlicesCondiment(IBeveragePtr&& beverage, unsigned quantity)
		: AbstractCondimentDecorator(std::move(beverage))
		, m_quantity(std::min(quantity, 5u)) // не больше 5 долек
	{
	}

protected:
	std::string GetCondimentDescription()const override
	{
		return "Chocolate slices x" + std::to_string(m_quantity);
	}

	double GetCondimentCost()const override
	{
		return 10 * m_quantity;
	}

private:
	unsigned m_quantity;
};

enum class LiquorType
{
	Chocolate,
	Walnut
};

class LiquorCondiment : public AbstractCondimentDecorator
{
public:
	LiquorCondiment(IBeveragePtr&& beverage, LiquorType type)
		: AbstractCondimentDecorator(std::move(beverage))
		, m_type(type)
	{
	}

protected:
	std::string GetCondimentDescription()const override
	{
		switch (m_type)
		{
		case LiquorType::Chocolate:
			return "ChocolateLiquor";
		case LiquorType::Walnut:
			return "WalnutLiquor";
		default:
			assert(false);
			throw std::logic_error("LiquorCondiment::GetCondimentDescription(): "
				"default switch branch should be unreachable");
		}
	}

	double GetCondimentCost()const override
	{
		return 50.0;
	}

private:
	LiquorType m_type;
};
