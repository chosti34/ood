#include "stdafx.h"
#include "SoldOutState.h"

using namespace with_state;

SoldOutState::SoldOutState(IGumballMachineContext& machine, std::ostream& output)
	: m_machine(machine)
	, m_output(output)
{
}

void SoldOutState::InsertCoin()
{
	m_output << "You can't insert a coin, the machine is sold out\n";
}

void SoldOutState::EjectCoin()
{
	if (m_machine.GetCoinsCount() == 0)
	{
		m_output << "You can't eject, you haven't inserted a coin yet\n";
	}
	else
	{
		while (m_machine.GetCoinsCount() != 0)
		{
			m_machine.ReleaseCoin();
		}
		m_output << "All coins returned\n";
	}
}

void SoldOutState::TurnCrank()
{
	m_output << "You turned but there's no gumballs\n";
}

void SoldOutState::Dispense()
{
	m_output << "No gumball dispensed\n";
}

void SoldOutState::Refill(unsigned count)
{
	assert(m_machine.GetGumballsCount() == 0);
	m_machine.SetBallsCount(count);
	if (count != 0)
	{
		if (m_machine.GetCoinsCount() == 0)
		{
			m_machine.SetNoCoinState();
		}
		else
		{
			m_machine.SetHasCoinState();
		}
	}
}

std::string SoldOutState::ToString() const
{
	return "sold out";
}
