#pragma once
#include "IState.h"
#include "IGumballMachineContext.h"
#include <ostream>

namespace with_state
{
class SoldOutState : public IState
{
public:
	SoldOutState(IGumballMachineContext& machine, std::ostream& output);

	void InsertCoin() override;
	void EjectCoin() override;

	void TurnCrank() override;
	void Dispense() override;
	void Refill(unsigned count) override;

	std::string ToString() const override;

private:
	IGumballMachineContext & m_machine;
	std::ostream& m_output;
};
}
