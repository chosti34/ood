#pragma once
#include <string>

class IGumballMachine
{
public:
	virtual ~IGumballMachine() = default;

	virtual void InsertCoin() = 0;
	virtual void EjectCoin() = 0;

	virtual void TurnCrank() = 0;
	virtual void Refill(unsigned count) = 0;

	virtual std::string ToString() const = 0;
};
