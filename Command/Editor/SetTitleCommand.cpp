#include "stdafx.h"
#include "SetTitleCommand.h"
#include "IDocumentControl.h"

SetTitleCommand::SetTitleCommand(const std::string& newTitle, const std::string& oldTitle)
	: m_newTitle(newTitle)
	, m_oldTitle(oldTitle)
{
}

void SetTitleCommand::Execute(IDocumentControl& control)
{
	control.DoSetTitle(m_newTitle);
}

void SetTitleCommand::Unexecute(IDocumentControl& control)
{
	control.DoSetTitle(m_oldTitle);
}
