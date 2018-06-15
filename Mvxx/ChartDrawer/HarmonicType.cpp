#include "stdafx.h"
#include "HarmonicType.h"

std::string ToString(HarmonicType type)
{
	switch (type)
	{
	case HarmonicType::Sin:
		return "sin";
	case HarmonicType::Cos:
		return "cos";
	default:
		throw std::logic_error("default switch branch should be unreachable");
	}
}
