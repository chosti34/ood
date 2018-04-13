#include "stdafx.h"
#include "SetTitleCommand.h"
#include "IDocumentCommandControl.h"

SetTitleCommand::SetTitleCommand(
	IDocumentCommandControl& control,
	const std::string& newTitle,
	const std::string& oldTitle)
	: m_control(control)
	, m_newTitle(newTitle)
	, m_oldTitle(oldTitle)
{
}

void SetTitleCommand::ExecuteImpl()
{
	m_control.DoSetTitle(m_newTitle);
}

void SetTitleCommand::UnexecuteImpl()
{
	m_control.DoSetTitle(m_oldTitle);
}
