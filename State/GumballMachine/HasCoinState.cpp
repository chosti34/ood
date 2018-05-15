#include "stdafx.h"
#include "HasCoinState.h"
#include <cassert>
#include <ostream>

using namespace with_state;

namespace
{
const unsigned MAX_COINS_COUNT = 5;
}

HasCoinState::HasCoinState(IGumballMachineContext& machine, std::ostream& output)
	: m_machine(machine)
	, m_output(output)
{
}

void HasCoinState::InsertCoin()
{
	if (m_machine.GetCoinsCount() < MAX_COINS_COUNT)
	{
		m_machine.AddCoin();
	}
	else
	{
		m_output << "You can't insert more than " << MAX_COINS_COUNT << " coins\n";
	}
}

void HasCoinState::EjectCoin()
{
	while (m_machine.GetCoinsCount() != 0)
	{
		m_machine.ReleaseCoin();
	}
	m_output << "All coins returned\n";
	m_machine.SetNoCoinState();
}

void HasCoinState::TurnCrank()
{
	assert(m_machine.GetCoinsCount() != 0);
	m_output << "You turned...\n";
	m_machine.ReleaseCoin();
	m_machine.SetSoldState();
}

void HasCoinState::Dispense()
{
	m_output << "No gumball dispensed\n";
}

std::string HasCoinState::ToString() const
{
	return "waiting for turn of crank";
}
