#include "stdafx.h"
#include "NoCoinState.h"

using namespace with_state;

NoCoinState::NoCoinState(IGumballMachineContext& context, std::ostream& output)
	: m_machine(context)
	, m_output(output)
{
}

void NoCoinState::InsertCoin()
{
	assert(m_machine.GetCoinsCount() == 0);
	m_machine.AddCoin();
	m_output << "You inserted a coin\n";
	m_machine.SetHasCoinState();
}

void NoCoinState::EjectCoin()
{
	m_output << "You haven't inserted a coin\n";
}

void NoCoinState::TurnCrank()
{
	m_output << "You turned but there's no coin\n";
}

void NoCoinState::Dispense()
{
	m_output << "You need to pay first\n";
}

void NoCoinState::Refill(unsigned count)
{
	m_machine.SetBallsCount(count);
	if (count == 0)
	{
		m_machine.SetSoldOutState();
	}
}

std::string NoCoinState::ToString() const
{
	return "waiting for coin";
}
