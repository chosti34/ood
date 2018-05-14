#pragma once
#include <iostream>
#include <boost/format.hpp>

namespace naive
{
class GumballMachine
{
	enum class State
	{
		NoBalls, // Нет жвачек
		NoQuarter, // Нет монеток
		HasQuarter, // Есть монетка
		Sold, // Жвачка продана
	};

public:
	GumballMachine(unsigned count = 0)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::NoBalls)
	{
	}

	void InsertQuarter()
	{
		switch (m_state)
		{
		case State::NoBalls:
			std::cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			std::cout << "You inserted a quarter\n";
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			std::cout << "You can't insert another quarter\n";
			break;
		case State::Sold:
			std::cout << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarter()
	{
		switch (m_state)
		{
		case State::NoBalls:
			std::cout << "You can't eject, you haven't inserted a quarter yet\n";
			break;
		case State::NoQuarter:
			std::cout << "You haven't inserted a quarter\n";
			break;
		case State::HasQuarter:
			std::cout << "Quarter returned\n";
			m_state = State::NoQuarter;
			break;
		case State::Sold:
			std::cout << "Sorry you already turned the crank\n";
			break;
		}
	}

	void TurnCrank()
	{
		switch (m_state)
		{
		case State::NoBalls:
			std::cout << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			std::cout << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			std::cout << "You turned...\n";
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			std::cout << "Turning twice doesn't give you another gumball\n";
			break;
		}
	}

	void Refill(unsigned count)
	{
		m_count = count;
		m_state = count > 0 ? State::NoQuarter : State::NoQuarter;
	}

	std::string ToString() const
	{
		std::string state =
			(m_state == State::NoBalls)		? "sold out" :
			(m_state == State::NoQuarter)	? "waiting for quarter" :
			(m_state == State::HasQuarter)	? "waiting for turn of crank"
											: "delivering a gumball";

		auto format = boost::format(R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Machine is %3%
)");

		return (format % m_count % (m_count != 1 ? "s" : "") % state).str();
	}

private:
	void Dispense()
	{
		switch (m_state)
		{
		case State::NoBalls:
			std::cout << "This is impossible\n";
			break;
		case State::NoQuarter:
			std::cout << "You need to pay first\n";
			break;
		case State::HasQuarter:
			std::cout << "This is impossible\n";
			break;
		case State::Sold:
			std::cout << "A gumball comes rolling out the slot\n";
			--m_count;
			if (m_count == 0)
			{
				std::cout << "Oops, out of gumballs\n";
				m_state = State::NoBalls;
			}
			else
			{
				m_state = State::NoQuarter;
			}
			break;
		}
	}

private:
	unsigned m_count;
	State m_state;
};
}
