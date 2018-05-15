#include "stdafx.h"
#include "GumballMachineWithState.h"
#include <boost/format.hpp>

using namespace with_state;

GumballMachine::GumballMachine(std::ostream& output, unsigned gumballs)
	: m_soldState(*this, output)
	, m_soldOutState(*this, output)
	, m_noCoinState(*this, output)
	, m_hasCoinState(*this, output)
	, m_state(&m_soldOutState)
	, m_gumballs(gumballs)
	, m_coins(0)
{
	if (m_gumballs > 0)
	{
		m_state = &m_noCoinState;
	}
}

void GumballMachine::InsertCoin()
{
	m_state->InsertCoin();
}

void GumballMachine::EjectCoin()
{
	m_state->EjectCoin();
}

void GumballMachine::TurnCrank()
{
	m_state->TurnCrank();
	m_state->Dispense();
}

std::string GumballMachine::ToString() const
{
	auto fmt = boost::format(R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%, %3% coin%4%
Machine is %5%)");
	return (fmt % m_gumballs % (m_gumballs != 1 ? "s" : "") %
		m_coins % (m_coins != 1 ? "s" : "") % m_state->ToString()).str();
}

void GumballMachine::ReleaseBall()
{
	--m_gumballs;
}

unsigned GumballMachine::GetGumballsCount() const
{
	return m_gumballs;
}

void GumballMachine::AddCoin()
{
	++m_coins;
}

void GumballMachine::ReleaseCoin()
{
	--m_coins;
}

unsigned GumballMachine::GetCoinsCount() const
{
	return m_coins;
}


void GumballMachine::SetSoldOutState()
{
	m_state = &m_soldOutState;
}

void GumballMachine::SetNoCoinState()
{
	m_state = &m_noCoinState;
}

void GumballMachine::SetSoldState()
{
	m_state = &m_soldState;
}

void GumballMachine::SetHasCoinState()
{
	m_state = &m_hasCoinState;
}
