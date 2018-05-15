#pragma once
#include <iostream>
#include <boost/format.hpp>

namespace naive
{
class GumballMachine
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

	void InsertCoin();
	void EjectCoin();

	void TurnCrank();
	void Refill(unsigned count);

	std::string ToString() const;

private:
	void Dispense();

private:
	unsigned m_gumballs;
	unsigned m_coins;
	State m_state;
	std::ostream& m_output;
};
}
