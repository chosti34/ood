#include "stdafx.h"

#include "../GumballMachineWithState.h"
#include "../NaiveGumballMachine.h"

#include <unordered_map>
#include <boost/test/tools/output_test_stream.hpp>
#include <boost/mpl/list.hpp>

namespace
{
enum class State
{
	Sold,
	SoldOut,
	HasCoin,
	NoCoin
};

const std::unordered_map<State, std::string> STATE_TO_STRING_MAPPING = {
	{ State::Sold, "delivering a gumball" },
	{ State::SoldOut, "sold out" },
	{ State::HasCoin, "waiting for turn of crank" },
	{ State::NoCoin, "waiting for coin" }
};

template <typename GumballMachineType>
void AssertGumballMachineState(
	const GumballMachineType& machine, unsigned gumballs, unsigned coins, State state)
{
	auto fmt = boost::format(R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%, %3% coin%4%
Machine is %5%)")
	% gumballs % (gumballs != 1 ? "s" : "")
	% coins % (coins != 1 ? "s" : "")
	% STATE_TO_STRING_MAPPING.at(state);
	BOOST_CHECK_EQUAL(machine.ToString(), fmt.str());
}
}

BOOST_AUTO_TEST_SUITE(CGumballMachine)
	typedef boost::mpl::list<with_state::GumballMachine, naive::GumballMachine> GumballMachineTypeList;

	struct GumballMachineFixture
	{
		template <typename Machine>
		std::unique_ptr<Machine> MakeGumballMachine(unsigned gumballs = 0, unsigned coins = 0)
		{
			auto machine = std::make_unique<Machine>(output, gumballs);
			for (unsigned i = 0; i < coins; ++i)
			{
				machine->InsertCoin();
			}
			return machine;
		}

		boost::test_tools::output_test_stream output;
	};

	BOOST_AUTO_TEST_SUITE(when_in_sold_out_state)
		BOOST_FIXTURE_TEST_CASE_TEMPLATE(
			has_zero_gumballs_inside, GumballMachine, GumballMachineTypeList, GumballMachineFixture)
		{
			auto machine = MakeGumballMachine<GumballMachine>();
			AssertGumballMachineState(*machine, 0, 0, State::SoldOut);
		}

		BOOST_FIXTURE_TEST_CASE_TEMPLATE(
			coins_cannot_be_inserted, GumballMachine, GumballMachineTypeList, GumballMachineFixture)
		{
			auto machine = MakeGumballMachine<GumballMachine>();
			machine->InsertCoin();
			AssertGumballMachineState(*machine, 0, 0, State::SoldOut);
			BOOST_CHECK(output.is_equal("You can't insert a coin, the machine is sold out\n"));
		}

		BOOST_FIXTURE_TEST_CASE_TEMPLATE(
			coins_can_be_ejected_if_there_are_left_some, GumballMachine, GumballMachineTypeList, GumballMachineFixture)
		{
			auto machine = MakeGumballMachine<GumballMachine>();
			machine->EjectCoin();
			AssertGumballMachineState(*machine, 0, 0, State::SoldOut);
			BOOST_CHECK(output.is_equal("You can't eject, you haven't inserted a coin yet\n"));

			// Вставляем две монетки в автомат, в котором только одна жвачка
			GumballMachine filledMachine(output, 1);
			filledMachine.InsertCoin();
			filledMachine.InsertCoin();
			AssertGumballMachineState(filledMachine, 1, 2, State::HasCoin);
			filledMachine.TurnCrank();
			output.flush();

			// Находимся в состоянии SoldOut и имеем одну монетку внутри
			AssertGumballMachineState(filledMachine, 0, 1, State::SoldOut);
			filledMachine.EjectCoin();
			BOOST_CHECK(output.is_equal("All coins returned\n"));
			AssertGumballMachineState(filledMachine, 0, 0, State::SoldOut);
		}

		BOOST_FIXTURE_TEST_CASE_TEMPLATE(turning_crank_doesnt_affect_anything, GumballMachine,
			GumballMachineTypeList, GumballMachineFixture)
		{
			auto machine = MakeGumballMachine<GumballMachine>();
			machine->TurnCrank();
			AssertGumballMachineState(*machine, 0, 0, State::SoldOut);
			BOOST_CHECK(output.is_equal("You turned but there's no gumballs\nNo gumball dispensed\n"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_in_no_coin_state)
		BOOST_FIXTURE_TEST_CASE_TEMPLATE(has_some_gumballs_inside, GumballMachine,
			GumballMachineTypeList, GumballMachineFixture)
		{
			auto machine = MakeGumballMachine<GumballMachine>(5);
			AssertGumballMachineState(*machine, 5, 0, State::NoCoin);
		}

		BOOST_FIXTURE_TEST_CASE_TEMPLATE(coins_insertion_leads_to_has_coin_state, GumballMachine,
			GumballMachineTypeList, GumballMachineFixture)
		{
			auto machine = MakeGumballMachine<GumballMachine>(5);
			machine->InsertCoin();
			BOOST_CHECK(output.is_equal("You inserted a coin\n"));
			AssertGumballMachineState(*machine, 5, 1, State::HasCoin);

			// Проверяем, что вставлено может быть до 5 монеток
			for (unsigned i = 0; i < 4; ++i)
			{
				machine->InsertCoin();
				AssertGumballMachineState(*machine, 5, 2 + i, State::HasCoin);
				BOOST_CHECK(output.is_equal("You inserted a coin\n"));
			}

			// Шестая монетка не вставится
			machine->InsertCoin();
			AssertGumballMachineState(*machine, 5, 5, State::HasCoin);
			BOOST_CHECK(output.is_equal("You can't insert more than 5 coins\n"));
		}

		BOOST_FIXTURE_TEST_CASE_TEMPLATE(coins_cant_be_ejected, GumballMachine,
			GumballMachineTypeList, GumballMachineFixture)
		{
			auto machine = MakeGumballMachine<GumballMachine>(5);
			machine->EjectCoin();
			AssertGumballMachineState(*machine, 5, 0, State::NoCoin);
			BOOST_CHECK(output.is_equal("You haven't inserted a coin\n"));
		}

		BOOST_FIXTURE_TEST_CASE_TEMPLATE(turning_crank_doesnt_affect_anything, GumballMachine,
			GumballMachineTypeList, GumballMachineFixture)
		{
			auto machine = MakeGumballMachine<GumballMachine>(5);
			machine->TurnCrank();
			AssertGumballMachineState(*machine, 5, 0, State::NoCoin);
			BOOST_CHECK(output.is_equal("You turned but there's no coin\nYou need to pay first\n"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_in_has_coin_state)
		BOOST_FIXTURE_TEST_CASE_TEMPLATE(has_some_gumballs_inside, GumballMachine,
			GumballMachineTypeList, GumballMachineFixture)
		{
			auto machine = MakeGumballMachine<GumballMachine>(5, 1);
			AssertGumballMachineState(*machine, 5, 1, State::HasCoin);
		}

		BOOST_FIXTURE_TEST_CASE_TEMPLATE(up_to_five_coins_can_be_inserted, GumballMachine,
			GumballMachineTypeList, GumballMachineFixture)
		{
			auto machine = MakeGumballMachine<GumballMachine>(5, 1);
			output.flush();
			AssertGumballMachineState(*machine, 5, 1, State::HasCoin);

			for (unsigned i = 0; i < 4; ++i)
			{
				machine->InsertCoin();
				AssertGumballMachineState(*machine, 5, 2 + i, State::HasCoin);
				BOOST_CHECK(output.is_equal("You inserted a coin\n"));
			}

			// Пытаемся вставить шестую монетку
			machine->InsertCoin();
			AssertGumballMachineState(*machine, 5, 5, State::HasCoin);
			BOOST_CHECK(output.is_equal("You can't insert more than 5 coins\n"));
		}

		BOOST_FIXTURE_TEST_CASE_TEMPLATE(ejecting_coins_leads_to_no_coin_state_and_that_can_be_undone_by_insertion,
			GumballMachine, GumballMachineTypeList, GumballMachineFixture)
		{
			auto machine = MakeGumballMachine<GumballMachine>(5, 1);

			machine->EjectCoin();
			AssertGumballMachineState(*machine, 5, 0, State::NoCoin);
			BOOST_CHECK("All coins returned\n");

			machine->InsertCoin();
			AssertGumballMachineState(*machine, 5, 1, State::HasCoin);
			BOOST_CHECK("You inserted a coin\n");
		}

		BOOST_FIXTURE_TEST_CASE_TEMPLATE(turning_crank_leads_to_dispensing_one_ball_with_no_quarter_state_or_sold_out_state,
			GumballMachine, GumballMachineTypeList, GumballMachineFixture)
		{
			auto machine = MakeGumballMachine<GumballMachine>(5, 1);
			output.flush();

			// Достаём 4 жвачки из автомата
			for (int i = 0; i < 4; ++i)
			{
				machine->TurnCrank();
				BOOST_CHECK(output.is_equal("You turned...\nA gumball comes rolling out the slot...\n"));
				AssertGumballMachineState(*machine, 4 - i, 0, State::NoCoin);

				// Возвращаемся в состояние HasCoin
				machine->InsertCoin();
				BOOST_CHECK(output.is_equal("You inserted a coin\n"));
			}

			// Достаём последнюю жвачку из автомата
			machine->TurnCrank();
			BOOST_CHECK(output.is_equal("You turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n"));
			AssertGumballMachineState(*machine, 0, 0, State::SoldOut);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_CASE_TEMPLATE(eject_coin_method_ejects_all_coins, GumballMachine, GumballMachineTypeList, GumballMachineFixture)
	{
		auto machine = MakeGumballMachine<GumballMachine>(5);
		AssertGumballMachineState(*machine, 5, 0, State::NoCoin);

		for (unsigned i = 0; i < 5; ++i)
		{
			machine->InsertCoin();
			BOOST_REQUIRE(output.is_equal("You inserted a coin\n"));
		}

		AssertGumballMachineState(*machine, 5, 5, State::HasCoin);
		machine->EjectCoin();
		BOOST_CHECK(output.is_equal("All coins returned\n"));
		AssertGumballMachineState(*machine, 5, 0, State::NoCoin);
	}

	BOOST_FIXTURE_TEST_CASE_TEMPLATE(coins_can_be_returned_when_there_is_no_gumballs_left, GumballMachine,
		GumballMachineTypeList, GumballMachineFixture)
	{
		// Создаём автомат с двумя жвачками внутри
		auto machine = MakeGumballMachine<GumballMachine>(2);
		AssertGumballMachineState(*machine, 2, 0, State::NoCoin);

		// Вставим пять монеток в автомат
		for (unsigned i = 0; i < 5; ++i)
		{
			machine->InsertCoin();
			BOOST_REQUIRE(output.is_equal("You inserted a coin\n"));
		}

		AssertGumballMachineState(*machine, 2, 5, State::HasCoin);

		// Купим две жвачки
		machine->TurnCrank();
		BOOST_REQUIRE(output.is_equal("You turned...\nA gumball comes rolling out the slot...\n"));

		machine->TurnCrank();
		BOOST_REQUIRE(output.is_equal("You turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n"));

		// Жвачек не осталось, однако в автомате лежат ещё три монетки!
		AssertGumballMachineState(*machine, 0, 3, State::SoldOut);

		machine->EjectCoin();
		AssertGumballMachineState(*machine, 0, 0, State::SoldOut);
		BOOST_CHECK(output.is_equal("All coins returned\n"));
	}
BOOST_AUTO_TEST_SUITE_END()
