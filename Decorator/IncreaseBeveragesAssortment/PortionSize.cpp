#include "stdafx.h"
#include "PortionSize.h"

std::string ToString(CoffeePortionSize portionSize)
{
	switch (portionSize)
	{
	case CoffeePortionSize::Standard:
		return "Standard";
	case CoffeePortionSize::Double:
		return "Double";
	default:
		assert(false);
		throw std::logic_error("ToString(CoffeePortionSize): default switch branch should be unreachable");
	}
}

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
