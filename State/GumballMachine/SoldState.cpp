#include "stdafx.h"
#include "SoldState.h"

using namespace with_state;

SoldState::SoldState(IGumballMachineContext& machine, std::ostream& output)
	: m_machine(machine)
	, m_output(output)
{
}

void SoldState::InsertCoin()
{
	m_output << "Please wait, we're already giving you a gumball\n";
}

void SoldState::EjectCoin()
{
	m_output << "Sorry you already turned the crank\n";
}

void SoldState::TurnCrank()
{
	m_output << "Turning twice doesn't get you another gumball\n";
}

void SoldState::Dispense()
{
	assert(m_machine.GetGumballsCount() != 0);
	m_machine.ReleaseBall();
	m_output << "A gumball comes rolling out the slot...\n";

	if (m_machine.GetGumballsCount() == 0)
	{
		m_output << "Oops, out of gumballs\n";
		m_machine.SetSoldOutState();
	}
	else if (m_machine.GetCoinsCount() == 0)
	{
		m_machine.SetNoCoinState();
	}
	else
	{
		m_machine.SetHasCoinState();
	}
}

void SoldState::Refill(unsigned count)
{
	m_output << "Can't refill gumballs in sold state\n";
}

std::string SoldState::ToString() const
{
	return "delivering a gumball";
}
