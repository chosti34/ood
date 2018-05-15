#pragma once
#include <string>

namespace with_state
{
class IState
{
public:
	virtual ~IState() = default;

	virtual void InsertCoin() = 0;
	virtual void EjectCoin() = 0;

	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual void Refill(unsigned count) = 0;

	virtual std::string ToString()const = 0;
};
}
