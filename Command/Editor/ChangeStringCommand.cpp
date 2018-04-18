#include "stdafx.h"
#include "ChangeStringCommand.h"

ChangeStringCommand::ChangeStringCommand(std::string& target, const std::string& newValue)
	: m_target(target)
	, m_newValue(newValue)
{
}

void ChangeStringCommand::ExecuteImpl()
{
	m_target.swap(m_newValue);
}

void ChangeStringCommand::UnexecuteImpl()
{
	m_target.swap(m_newValue);
}
