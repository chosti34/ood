#pragma once
#include "IState.h"
#include "IGumballMachineContext.h"

namespace with_state
{
class HasCoinState : public IState
{
public:
	HasCoinState(IGumballMachineContext& machine, std::ostream& output);

	void InsertCoin() override;
	void EjectCoin() override;

	void TurnCrank() override;
	void Dispense() override;

	std::string ToString() const override;

private:
	IGumballMachineContext & m_machine;
	std::ostream& m_output;
};
}
