#include "stdafx.h"
#include "AbstractCommand.h"

AbstractCommand::AbstractCommand()
	: m_executed(false)
{
}

void AbstractCommand::Execute()
{
	if (m_executed)
	{
		throw std::logic_error("command can't be executed twice");
	}
	ExecuteImpl();
	m_executed = true;
}

void AbstractCommand::Unexecute()
{
	if (!m_executed)
	{
		throw std::logic_error("command can't be unexecuted twice");
	}
	UnexecuteImpl();
	m_executed = false;
}

bool AbstractCommand::IsExecuted()const
{
	return m_executed;
}
