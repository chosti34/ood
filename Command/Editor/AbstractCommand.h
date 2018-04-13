#pragma once
#include "ICommand.h"

class AbstractCommand : public ICommand
{
public:
	AbstractCommand();

	void Execute() override;
	void Unexecute() override;

protected:
	bool IsExecuted()const;

	virtual void ExecuteImpl() = 0;
	virtual void UnexecuteImpl() = 0;

private:
	bool m_executed;
};
