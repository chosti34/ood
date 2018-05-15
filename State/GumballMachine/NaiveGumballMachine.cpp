#include "stdafx.h"
#include "NaiveGumballMachine.h"

namespace
{
const unsigned MAX_COINS_COUNT = 5;
}

using namespace naive;

GumballMachine::GumballMachine(std::ostream& output, unsigned gumballs /* = 0 */)
	: m_gumballs(gumballs)
	, m_state(gumballs > 0 ? State::NoCoin : State::SoldOut)
	, m_coins(0)
	, m_output(output)
{
}

void GumballMachine::InsertCoin()
{
	switch (m_state)
	{
	case State::SoldOut:
		m_output << "You can't insert a coin, the machine is sold out\n";
		break;
	case State::NoCoin:
		assert(m_coins == 0);
		++m_coins;
		m_output << "You inserted a coin\n";
		m_state = State::HasCoin;
		break;
	case State::HasCoin:
		if (m_coins < MAX_COINS_COUNT)
		{
			++m_coins;
			m_output << "You inserted a coin\n";
		}
		else
		{
			m_output << "You can't insert more than " << MAX_COINS_COUNT << " coins\n";
		}
		break;
	case State::Sold:
		m_output << "Please wait, we're already giving you a gumball\n";
		break;
	}
}

void GumballMachine::EjectCoin()
{
	switch (m_state)
	{
	case State::SoldOut:
		if (m_coins == 0)
		{
			m_output << "You can't eject, you haven't inserted a coin yet\n";
		}
		else
		{
			while (m_coins != 0)
			{
				--m_coins;
			}
			m_output << "All coins returned\n";
		}
		break;
	case State::NoCoin:
		m_output << "You haven't inserted a coin\n";
		break;
	case State::HasCoin:
		while (m_coins != 0)
		{
			--m_coins;
		}
		m_output << "All coins returned\n";
		m_state = State::NoCoin;
		break;
	case State::Sold:
		m_output << "Sorry you already turned the crank\n";
		break;
	}
}

void GumballMachine::TurnCrank()
{
	switch (m_state)
	{
	case State::SoldOut:
		m_output << "You turned but there's no gumballs\n";
		break;
	case State::NoCoin:
		m_output << "You turned but there's no coin\n";
		break;
	case State::HasCoin:
		assert(m_coins != 0);
		if (m_gumballs != 0)
		{
			m_output << "You turned...\n";
			--m_coins;
			m_state = State::Sold;
		}
		break;
	case State::Sold:
		m_output << "Turning twice doesn't give you another gumball\n";
		break;
	}
	Dispense();
}

void GumballMachine::Refill(unsigned count)
{
	m_gumballs = count;
	m_state = count > 0 ? State::NoCoin : State::NoCoin;
}

std::string GumballMachine::ToString() const
{
	std::string state =
		(m_state == State::SoldOut) ? "sold out" :
		(m_state == State::NoCoin) ? "waiting for coin" :
		(m_state == State::HasCoin) ? "waiting for turn of crank"
		: "delivering a gumball";

	auto fmt = boost::format(R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%, %3% coin%4%
Machine is %5%)");

	return (fmt % m_gumballs % (m_gumballs != 1 ? "s" : "")
		% m_coins % (m_coins != 1 ? "s" : "") % state).str();
}

void GumballMachine::Dispense()
{
	switch (m_state)
	{
	case State::SoldOut:
		m_output << "No gumball dispensed\n";
		break;
	case State::NoCoin:
		m_output << "You need to pay first\n";
		break;
	case State::HasCoin:
		m_output << "No gumball dispensed\n";
		break;
	case State::Sold:
		assert(m_gumballs != 0);
		--m_gumballs;
		m_output << "A gumball comes rolling out the slot...\n";

		if (m_gumballs == 0)
		{
			m_output << "Oops, out of gumballs\n";
			m_state = State::SoldOut;
		}
		else if (m_coins == 0)
		{
			m_state = State::NoCoin;
		}
		else
		{
			m_state = State::HasCoin;
		}
		break;
	}
}
