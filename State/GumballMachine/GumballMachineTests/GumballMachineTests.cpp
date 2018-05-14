#include "stdafx.h"
#include "../GumballMachineWithState.h"
#include <boost/format.hpp>
#include <unordered_map>

namespace
{
enum class State
{
	Sold,
	SoldOut,
	HasQuarter,
	NoQuarter
};

const std::unordered_map<State, std::string> STATE_TO_STRING_MAPPING = {
	{ State::Sold, "delivering a gumball" },
	{ State::SoldOut, "sold out" },
	{ State::HasQuarter, "waiting for turn of crank" },
	{ State::NoQuarter, "waiting for quarter" }
};

void AssertGumballMachineState(const with_state::CGumballMachine& machine, unsigned count, State state)
{
	const std::string info = (boost::format(R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%)") % count % (count != 1 ? "s" : "") % STATE_TO_STRING_MAPPING.at(state)).str();
	BOOST_CHECK_EQUAL(machine.ToString(), info);
}
}

BOOST_AUTO_TEST_SUITE(GumballMachine)
	BOOST_AUTO_TEST_CASE(when_created_has_zero_balls)
	{
		with_state::CGumballMachine machine;
		AssertGumballMachineState(machine, 0, State::SoldOut);
	}
BOOST_AUTO_TEST_SUITE_END()
