#pragma once
#include <cassert>
#include "AbstractBeverage.h"

class Tea : public AbstractBeverage
{
public:
	// Можно было бы ввести подклассы
	enum class Kind
	{
		Green,
		White,
		Black,
		Oolong
	};

public:
	Tea(Kind kind)
		: AbstractBeverage(ToString(kind) + "Tea")
	{
	}

	double GetCost()const override
	{
		return 30.0;
	}

private:
	static std::string ToString(Kind kind)
	{
		switch (kind)
		{
		case Kind::Green:
			return "Green";
		case Kind::White:
			return "White";
		case Kind::Black:
			return "Black";
		case Kind::Oolong:
			return "Oolong";
		default:
			assert(false);
			throw std::logic_error("Tea::ToString(Kind): default switch branch should be unreachable");
		}
	}
};
