#include "stdafx.h"
#include "GumballMachineWithState.h"
#include "NaiveGumballMachine.h"
#include "Menu.h"

namespace
{
class GumballMachinesInteractor
{
public:
	GumballMachinesInteractor()
		: m_naiveMachine(std::cout)
		, m_machineWithState(std::cout)
		, m_selectedMachine(&m_naiveMachine)
	{
		using namespace std;
		using namespace placeholders;
		m_menu.AddItem("Exit", "Exit from menu", [this](istream&) { m_menu.Exit(); });
		m_menu.AddItem("Help", "Show menu instructions", [this](istream&) { m_menu.ShowInstructions(); });
		m_menu.AddItem("SwitchMachine", "Switch selected gumball machine",
			bind(&GumballMachinesInteractor::SwitchMachine, this, _1));
		m_menu.AddItem("InsertCoin", "Insert coin to selected machine",
			bind(&GumballMachinesInteractor::InsertCoin, this, _1));
		m_menu.AddItem("EjectCoin", "Ejects all coins from selected machine",
			bind(&GumballMachinesInteractor::EjectCoin, this, _1));
		m_menu.AddItem("TurnCrank", "Turn crank of the selected machine",
			bind(&GumballMachinesInteractor::TurnCrank, this, _1));
		m_menu.AddItem("Refill", "Refill machine with some gumballs",
			bind(&GumballMachinesInteractor::Refill, this, _1));
		m_menu.AddItem("ToString", "Get detailed information",
			bind(&GumballMachinesInteractor::ToString, this, _1));
	}

	void StartInteraction()
	{
		m_menu.Run();
	}

private:
	void SwitchMachine(std::istream&)
	{
		if (m_selectedMachine == &m_naiveMachine)
		{
			m_selectedMachine = &m_machineWithState;
		}
		else
		{
			m_selectedMachine = &m_naiveMachine;
		}
	}

	void InsertCoin(std::istream&)
	{
		m_selectedMachine->InsertCoin();
	}

	void EjectCoin(std::istream&)
	{
		m_selectedMachine->EjectCoin();
	}

	void TurnCrank(std::istream&)
	{
		m_selectedMachine->TurnCrank();
	}

	void Refill(std::istream& strm)
	{
		unsigned count;
		if (strm >> count)
		{
			m_selectedMachine->Refill(count);
		}
		else
		{
			std::cout << "Provide gumballs count\n";
		}
	}

	void ToString(std::istream&)
	{
		std::cout << "Selected machine: " <<
			(m_selectedMachine == &m_naiveMachine ? "naive" : "with state pattern") << "\n";
		std::cout << m_selectedMachine->ToString() << "\n";
	}

	Menu m_menu;
	naive::GumballMachine m_naiveMachine;
	with_state::GumballMachine m_machineWithState;
	IGumballMachine* m_selectedMachine;
};
}

int main()
{
	GumballMachinesInteractor interactor;
	interactor.StartInteraction();
	return 0;
}
