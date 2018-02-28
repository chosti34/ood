#pragma once
#include <cassert>
#include "AbstractBeverage.h"

// Можно было бы ввести подклассы
enum class MilkshakePortionSize
{
	Small,
	Medium,
	Large
};

std::string ToString(MilkshakePortionSize portionSize)
{
	switch (portionSize)
	{
	case MilkshakePortionSize::Small:
		return "Small";
	case MilkshakePortionSize::Medium:
		return "Medium";
	case MilkshakePortionSize::Large:
		return "Large";
	default:
		assert(false);
		throw std::logic_error("ToString(MilkshakePortionSize): "
			"default switch branch should be unreachable");
	}
}

class Milkshake : public AbstractBeverage
{
public:
	Milkshake(MilkshakePortionSize portionSize)
		: AbstractBeverage(ToString(portionSize) + "Milkshake")
		, m_portionSize(portionSize)
	{
	}

	double GetCost()const override
	{
		switch (m_portionSize)
		{
		case MilkshakePortionSize::Small:
			return 50.0;
		case MilkshakePortionSize::Medium:
			return 60.0;
		case MilkshakePortionSize::Large:
			return 80.0;
		default:
			assert(false);
			throw std::logic_error("Milkshake::GetCost(): default "
				"switch branch should be unreachable");
		}
	}

private:
	MilkshakePortionSize m_portionSize;
};
