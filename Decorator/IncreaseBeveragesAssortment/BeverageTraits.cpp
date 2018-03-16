#include "stdafx.h"
#include "BeverageTraits.h"
#include <cassert>

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
		throw std::logic_error("ToString(CoffeePortionSize): "
			"default switch branch should be unreachable");
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

std::string ToString(TeaKind kind)
{
	switch (kind)
	{
	case TeaKind::Green:
		return "Green";
	case TeaKind::White:
		return "White";
	case TeaKind::Black:
		return "Black";
	case TeaKind::Oolong:
		return "Oolong";
	default:
		assert(false);
		throw std::logic_error("Tea::ToString(Kind): "
			"default switch branch should be unreachable");
	}
}
