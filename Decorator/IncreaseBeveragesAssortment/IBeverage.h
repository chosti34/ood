#pragma once
#include <string>
#include <memory>

class IBeverage
{
public:
	virtual ~IBeverage() = default;
	virtual std::string GetDescription()const = 0;
	virtual double GetCost()const = 0;
};

using IBeveragePtr = std::unique_ptr<IBeverage>;
