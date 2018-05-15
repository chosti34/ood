#pragma once
#include "IState.h"
#include "IGumballMachineContext.h"

namespace with_state
{
class NoCoinState : public IState
{
public:
	NoCoinState(IGumballMachineContext& machine, std::ostream& output);

	void InsertCoin() override;
	void EjectCoin() override;

	void TurnCrank() override;
	void Dispense() override;
	void Refill(unsigned count) override;

	std::string ToString()const override;

private:
	IGumballMachineContext& m_machine;
	std::ostream& m_output;
};
}
