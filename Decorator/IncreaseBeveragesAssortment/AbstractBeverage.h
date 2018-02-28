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
