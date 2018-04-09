#include "stdafx.h"
#include "SetTitleCommand.h"
#include "IDocumentCommandControl.h"

SetTitleCommand::SetTitleCommand(const std::string& newTitle, const std::string& oldTitle)
	: m_newTitle(newTitle)
	, m_oldTitle(oldTitle)
{
}

void SetTitleCommand::Execute(IDocumentCommandControl& control)
{
	control.DoSetTitle(m_newTitle);
}

void SetTitleCommand::Unexecute(IDocumentCommandControl& control)
{
	control.DoSetTitle(m_oldTitle);
}
