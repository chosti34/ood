#pragma once
#include "NoCoinState.h"
#include "HasCoinState.h"
#include "SoldState.h"
#include "SoldOutState.h"
#include "IGumballMachine.h"

namespace with_state
{
class GumballMachine
	: public IGumballMachine
	, private IGumballMachineContext
{
public:
	GumballMachine(std::ostream& output, unsigned gumballs = 0);

	void InsertCoin() override;
	void EjectCoin() override;

	void TurnCrank() override;
	void Refill(unsigned count) override;

	std::string ToString() const override;

private:
	void SetBallsCount(unsigned count) override;
	void ReleaseBall() override;
	unsigned GetGumballsCount() const override;

	void AddCoin() override;
	void ReleaseCoin() override;
	unsigned GetCoinsCount() const override;

	void SetSoldOutState() override;
	void SetNoCoinState() override;
	void SetSoldState() override;
	void SetHasCoinState() override;

private:
	unsigned m_gumballs;
	unsigned m_coins;

	NoCoinState m_noCoinState;
	HasCoinState m_hasCoinState;
	SoldState m_soldState;
	SoldOutState m_soldOutState;
	IState* m_state;
};
}
