#pragma once
#include <iostream>
#include <boost/format.hpp>

namespace with_state
{
struct IState
{
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarter() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual std::string ToString()const = 0;
	virtual ~IState() = default;
};

struct IGumballMachine
{
	virtual void ReleaseBall() = 0;
	virtual unsigned GetBallCount()const = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumballMachine() = default;
};

class SoldState : public IState
{
public:
	SoldState(IGumballMachine& gumballMachine, std::ostream& output)
		: m_gumballMachine(gumballMachine)
		, m_output(output)
	{
	}

	void InsertQuarter() override
	{
		m_output << "Please wait, we're already giving you a gumball\n";
	}

	void EjectQuarter() override
	{
		m_output << "Sorry you already turned the crank\n";
	}

	void TurnCrank() override
	{
		m_output << "Turning twice doesn't get you another gumball\n";
	}

	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();
		if (m_gumballMachine.GetBallCount() == 0)
		{
			m_output << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else
		{
			m_gumballMachine.SetNoQuarterState();
		}
	}

	std::string ToString()const override
	{
		return "delivering a gumball";
	}

private:
	IGumballMachine& m_gumballMachine;
	std::ostream& m_output;
};

class SoldOutState : public IState
{
public:
	SoldOutState(IGumballMachine& gumballMachine, std::ostream& output)
		: m_gumballMachine(gumballMachine)
		, m_output(output)
	{
	}

	void InsertQuarter() override
	{
		m_output << "You can't insert a quarter, the machine is sold out\n";
	}

	void EjectQuarter() override
	{
		m_output << "You can't eject, you haven't inserted a quarter yet\n";
	}

	void TurnCrank() override
	{
		m_output << "You turned but there's no gumballs\n";
	}

	void Dispense() override
	{
		m_output << "No gumball dispensed\n";
	}

	std::string ToString()const override
	{
		return "sold out";
	}

private:
	IGumballMachine& m_gumballMachine;
	std::ostream& m_output;
};

class HasQuarterState : public IState
{
public:
	HasQuarterState(IGumballMachine& gumballMachine, std::ostream& output)
		: m_gumballMachine(gumballMachine)
		, m_output(output)
	{
	}

	void InsertQuarter() override
	{
		m_output << "You can't insert another quarter\n";
	}

	void EjectQuarter() override
	{
		m_output << "Quarter returned\n";
		m_gumballMachine.SetNoQuarterState();
	}

	void TurnCrank() override
	{
		m_output << "You turned...\n";
		m_gumballMachine.SetSoldState();
	}

	void Dispense() override
	{
		m_output << "No gumball dispensed\n";
	}

	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}

private:
	IGumballMachine& m_gumballMachine;
	std::ostream& m_output;
};

class NoQuarterState : public IState
{
public:
	NoQuarterState(IGumballMachine& gumballMachine, std::ostream& output)
		: m_gumballMachine(gumballMachine)
		, m_output(output)
	{
	}

	void InsertQuarter() override
	{
		m_output << "You inserted a quarter\n";
		m_gumballMachine.SetHasQuarterState();
	}

	void EjectQuarter() override
	{
		m_output << "You haven't inserted a quarter\n";
	}

	void TurnCrank() override
	{
		m_output << "You turned but there's no quarter\n";
	}

	void Dispense() override
	{
		m_output << "You need to pay first\n";
	}

	std::string ToString()const override
	{
		return "waiting for quarter";
	}

private:
	IGumballMachine& m_gumballMachine;
	std::ostream& m_output;
};

class GumballMachine : private IGumballMachine
{
public:
	GumballMachine(std::ostream& output, unsigned numBalls = 0)
		: m_soldState(*this, output)
		, m_soldOutState(*this, output)
		, m_noQuarterState(*this, output)
		, m_hasQuarterState(*this, output)
		, m_state(&m_soldOutState)
		, m_count(numBalls)
		, m_output(output)
	{
		if (m_count > 0)
		{
			m_state = &m_noQuarterState;
		}
	}

	void EjectQuarter()
	{
		m_state->EjectQuarter();
	}

	void InsertQuarter()
	{
		m_state->InsertQuarter();
	}

	void TurnCrank()
	{
		m_state->TurnCrank();
		m_state->Dispense();
	}

	std::string ToString()const
	{
		auto fmt = boost::format(R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%)");
		return (fmt % m_count % (m_count != 1 ? "s" : "") % m_state->ToString()).str();
	}

private:
	unsigned GetBallCount()const override
	{
		return m_count;
	}

	void ReleaseBall() override
	{
		if (m_count != 0)
		{
			m_output << "A gumball comes rolling out the slot...\n";
			--m_count;
		}
	}

	void SetSoldOutState() override
	{
		m_state = &m_soldOutState;
	}

	void SetNoQuarterState() override
	{
		m_state = &m_noQuarterState;
	}

	void SetSoldState() override
	{
		m_state = &m_soldState;
	}

	void SetHasQuarterState() override
	{
		m_state = &m_hasQuarterState;
	}

private:
	unsigned m_count = 0;
	SoldState m_soldState;
	SoldOutState m_soldOutState;
	NoQuarterState m_noQuarterState;
	HasQuarterState m_hasQuarterState;
	IState* m_state;
	std::ostream& m_output;
};
}
