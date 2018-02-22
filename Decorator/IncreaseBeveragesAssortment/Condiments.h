#pragma once
#include "IBeverage.h"

// ������� ��������� "������� � �������". ����� �������� ��������.
class CondimentDecorator : public IBeverage
{
public:
	std::string GetDescription()const override
	{
		// �������� ��������������� ������� ����������� � �������� �������������� �������
		return m_beverage->GetDescription() + ", " + GetCondimentDescription();
	}

	double GetCost()const override
	{
		// ��������� ������������ �� ��������� ������� � ��������� �������������� �������
		return m_beverage->GetCost() + GetCondimentCost();
	}

protected:
	CondimentDecorator(IBeveragePtr&& beverage)
		: m_beverage(std::move(beverage))
	{
	}

	// ��������� � �������� ������� ����������� � ������� ���������� �����������
	virtual std::string GetCondimentDescription()const = 0;
	virtual double GetCondimentCost()const = 0;

private:
	IBeveragePtr m_beverage;
};

// ������� �� ������
class Cinnamon : public CondimentDecorator
{
public:
	Cinnamon(IBeveragePtr&& beverage)
		: CondimentDecorator(std::move(beverage))
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

// �������� �������
class Lemon : public CondimentDecorator
{
public:
	Lemon(IBeveragePtr&& beverage, unsigned quantity = 1)
		: CondimentDecorator(std::move(beverage))
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
	Dry,	// ����� �� (��� ������� ��������� �������)
	Water	// ������� ������ �� ����
};

// ������� "������ ����". ������������ ����� � ����������� �������, ���
//  ������ �� ��������� � ��������
class IceCubes : public CondimentDecorator
{
public:
	IceCubes(IBeveragePtr&& beverage, unsigned quantity, IceCubeType type = IceCubeType::Water)
		: CondimentDecorator(std::move(beverage))
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

class Syrup : public CondimentDecorator
{
public:
	Syrup(IBeveragePtr&& beverage, SyrupType type)
		: CondimentDecorator(std::move(beverage))
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

// ��������� �������
class ChocolateCrumbs : public CondimentDecorator
{
public:
	ChocolateCrumbs(IBeveragePtr&& beverage, unsigned mass)
		: CondimentDecorator(std::move(beverage))
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

// ��������� �������
class CoconutFlakes : public CondimentDecorator
{
public:
	CoconutFlakes(IBeveragePtr&& beverage, unsigned mass)
		: CondimentDecorator(std::move(beverage))
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
