#pragma once
#include <cassert>
#include "AbstractBeverage.h"
#include "BeverageTraits.h"

class Tea : public AbstractBeverage
{
public:
	Tea(TeaKind kind)
		: AbstractBeverage(ToString(kind) + "Tea")
	{
	}

	double GetCost()const override
	{
		return 30.0;
	}
};
