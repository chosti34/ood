#pragma once
#include <ostream>
#include "IGumballMachine.h"

namespace naive
{
class GumballMachine : public IGumballMachine
{
	enum class State
	{
		NoCoin,
		HasCoin,
		Sold,
		SoldOut
	};

public:
	GumballMachine(std::ostream& output, unsigned gumballs = 0);

	void InsertCoin() override;
	void EjectCoin() override;

	void TurnCrank() override;
	void Refill(unsigned count) override;

	std::string ToString() const override;

private:
	void Dispense();

private:
	unsigned m_gumballs;
	unsigned m_coins;
	State m_state;
	std::ostream& m_output;
};
}
