#include "stdafx.h"
#include "ReplaceTextCommand.h"
#include "IDocument.h"

ReplaceTextCommand::ReplaceTextCommand(const std::string& newText, const std::string& oldText, size_t index)
	: m_newText(newText)
	, m_oldText(oldText)
	, m_index(index)
{
}

void ReplaceTextCommand::Execute(IDocumentCommandControl& control)
{
	control.DoReplaceText(m_newText, m_index);
}

void ReplaceTextCommand::Unexecute(IDocumentCommandControl& control)
{
	control.DoReplaceText(m_oldText, m_index);
}
