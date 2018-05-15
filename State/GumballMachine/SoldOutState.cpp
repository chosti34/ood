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
	m_output << "You can't insert a quarter, the machine is sold out\n";
}

void SoldOutState::EjectCoin()
{
	m_output << "You can't eject, you haven't inserted a quarter yet\n";
}

void SoldOutState::TurnCrank()
{
	m_output << "You turned but there's no gumballs\n";
}

void SoldOutState::Dispense()
{
	m_output << "No gumball dispensed\n";
}

std::string with_state::SoldOutState::ToString() const
{
	return "sold out";
}
