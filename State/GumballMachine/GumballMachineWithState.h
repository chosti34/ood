#pragma once
#include "NoCoinState.h"
#include "HasCoinState.h"
#include "SoldState.h"
#include "SoldOutState.h"

namespace with_state
{
class GumballMachine : private IGumballMachineContext
{
public:
	GumballMachine(std::ostream& output, unsigned gumballs = 0);

	void InsertCoin();
	void EjectCoin();

	void TurnCrank();
	void Refill(unsigned count);

	std::string ToString() const;

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
