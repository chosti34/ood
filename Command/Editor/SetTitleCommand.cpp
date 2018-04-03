#include "stdafx.h"
#include "SetTitleCommand.h"
#include "IDocument.h"

SetTitleCommand::SetTitleCommand(const std::string& title)
	: m_newTitle(title)
	, m_oldTitle()
{
}

bool SetTitleCommand::Execute(IDocument& document)
{
	m_oldTitle = document.GetTitle();
	document.SetTitle(m_newTitle);
	return true;
}

void SetTitleCommand::Undo(IDocument& document)
{
	assert(m_oldTitle.is_initialized());
	document.SetTitle(m_oldTitle.value());
}

void SetTitleCommand::Redo(IDocument& document)
{
	document.SetTitle(m_newTitle);
}
