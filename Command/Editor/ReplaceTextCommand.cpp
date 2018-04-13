#include "stdafx.h"
#include "ReplaceTextCommand.h"
#include "IDocument.h"

ReplaceTextCommand::ReplaceTextCommand(IParagraph& paragraph, const std::string& newText)
	: m_paragraph(paragraph)
	, m_newText(newText)
	, m_oldText(paragraph.GetText())
{
}

void ReplaceTextCommand::ExecuteImpl()
{
	m_paragraph.SetText(m_newText);
}

void ReplaceTextCommand::UnexecuteImpl()
{
	m_paragraph.SetText(m_oldText);
}
