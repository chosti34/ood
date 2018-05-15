#pragma once

namespace with_state
{
class IGumballMachineContext
{
public:
	virtual ~IGumballMachineContext() = default;

	virtual void SetBallsCount(unsigned count) = 0;
	virtual void ReleaseBall() = 0;
	virtual unsigned GetGumballsCount()const = 0;

	virtual void AddCoin() = 0;
	virtual void ReleaseCoin() = 0;
	virtual unsigned GetCoinsCount()const = 0;

	virtual void SetNoCoinState() = 0;
	virtual void SetHasCoinState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetSoldOutState() = 0;
};
}
