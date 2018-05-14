#include "stdafx.h"
#include "../GumballMachineWithState.h"
#include <boost/test/tools/output_test_stream.hpp>
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

void AssertGumballMachineState(const with_state::GumballMachine& machine, unsigned count, State state)
{
	const std::string info = (boost::format(R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%)") % count % (count != 1 ? "s" : "") % STATE_TO_STRING_MAPPING.at(state)).str();
	BOOST_CHECK_EQUAL(machine.ToString(), info);
}
}

BOOST_AUTO_TEST_SUITE(CGumballMachine)
	struct GumballMachineInSoldOutStateFixture
	{
		GumballMachineInSoldOutStateFixture(unsigned count = 0)
			: machine(output, count)
		{
		}

		boost::test_tools::output_test_stream output;
		with_state::GumballMachine machine;
	};

	BOOST_FIXTURE_TEST_SUITE(when_in_sold_out_state, GumballMachineInSoldOutStateFixture)
		BOOST_AUTO_TEST_CASE(has_zero_gumballs_inside)
		{
			AssertGumballMachineState(machine, 0, State::SoldOut);
		}

		BOOST_AUTO_TEST_CASE(quarter_cant_be_inserted)
		{
			machine.InsertQuarter();
			AssertGumballMachineState(machine, 0, State::SoldOut);
			BOOST_CHECK(output.is_equal("You can't insert a quarter, the machine is sold out\n"));
		}

		BOOST_AUTO_TEST_CASE(quarter_cannot_be_ejected)
		{
			machine.EjectQuarter();
			AssertGumballMachineState(machine, 0, State::SoldOut);
			BOOST_CHECK(output.is_equal("You can't eject, you haven't inserted a quarter yet\n"));
		}

		BOOST_AUTO_TEST_CASE(turning_crank_doesnt_affect_anything)
		{
			machine.TurnCrank();
			AssertGumballMachineState(machine, 0, State::SoldOut);
			BOOST_CHECK(output.is_equal("You turned but there's no gumballs\nNo gumball dispensed\n"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct GumballMachineInNoQuarterStateFixture
	{
		GumballMachineInNoQuarterStateFixture()
			: machine(output, 5)
		{
		}

		boost::test_tools::output_test_stream output;
		with_state::GumballMachine machine;
	};

	BOOST_FIXTURE_TEST_SUITE(when_in_no_quarter_state, GumballMachineInNoQuarterStateFixture)
		BOOST_AUTO_TEST_CASE(has_some_gumballs_inside)
		{
			AssertGumballMachineState(machine, 5, State::NoQuarter);
		}

		BOOST_AUTO_TEST_CASE(quarter_insertion_leads_to_has_quarter_state)
		{
			machine.InsertQuarter();
			AssertGumballMachineState(machine, 5, State::HasQuarter);
			BOOST_CHECK(output.is_equal("You inserted a quarter\n"));
		}

		BOOST_AUTO_TEST_CASE(quarter_cant_be_ejected)
		{
			machine.EjectQuarter();
			AssertGumballMachineState(machine, 5, State::NoQuarter);
			BOOST_CHECK(output.is_equal("You haven't inserted a quarter\n"));
		}

		BOOST_AUTO_TEST_CASE(turning_crank_doesnt_affect_anything)
		{
			machine.TurnCrank();
			AssertGumballMachineState(machine, 5, State::NoQuarter);
			BOOST_CHECK(output.is_equal("You turned but there's no quarter\nYou need to pay first\n"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct GumballMachineInHasQuarterState
	{
		GumballMachineInHasQuarterState()
			: machine(output, 5)
		{
			machine.InsertQuarter();
			output.flush();
		}

		boost::test_tools::output_test_stream output;
		with_state::GumballMachine machine;
	};

	BOOST_FIXTURE_TEST_SUITE(when_in_has_quarter_state, GumballMachineInHasQuarterState)
		BOOST_AUTO_TEST_CASE(has_some_gumballs_inside)
		{
			AssertGumballMachineState(machine, 5, State::HasQuarter);
		}

		BOOST_AUTO_TEST_CASE(another_quarter_cant_be_inserted)
		{
			machine.InsertQuarter();
			AssertGumballMachineState(machine, 5, State::HasQuarter);
			BOOST_CHECK(output.is_equal("You can't insert another quarter\n"));
		}

		BOOST_AUTO_TEST_CASE(ejecting_quarter_leads_to_no_quarter_state_and_that_can_be_undone_by_insertion)
		{
			machine.EjectQuarter();
			AssertGumballMachineState(machine, 5, State::NoQuarter);
			BOOST_CHECK("Quarter returned\n");

			machine.InsertQuarter();
			AssertGumballMachineState(machine, 5, State::HasQuarter);
			BOOST_CHECK("You inserted a quarter\n");
		}

		BOOST_AUTO_TEST_CASE(turning_crank_leads_to_dispensing_one_ball_with_no_quarter_state_or_sold_out_state)
		{
			// Достаём 4 жвачки из автомата
			for (int i = 0; i < 4; ++i)
			{
				machine.TurnCrank();
				BOOST_CHECK(output.is_equal("You turned...\nA gumball comes rolling out the slot...\n"));
				AssertGumballMachineState(machine, 4 - i, State::NoQuarter);

				// Возвращаемся в состояние HasQuarter
				machine.InsertQuarter();
				BOOST_CHECK(output.is_equal("You inserted a quarter\n"));
			}

			// Достаём последнюю жвачку из автомата
			machine.TurnCrank();
			BOOST_CHECK(output.is_equal("You turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n"));
			AssertGumballMachineState(machine, 0, State::SoldOut);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
