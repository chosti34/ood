#include "stdafx.h"
#include "ReplaceTextCommand.h"
#include "IDocument.h"

ReplaceTextCommand::ReplaceTextCommand(size_t pos, const std::string& text)
	: m_pos(pos)
	, m_newText(text)
	, m_oldText()
{
}

bool ReplaceTextCommand::Execute(IDocument& document)
{
	auto paragraph = document.GetItem(m_pos)->GetParagraph();
	assert(paragraph);
	m_oldText = paragraph->GetText();
	paragraph->SetText(m_newText);
	return true;
}

void ReplaceTextCommand::Undo(IDocument& document)
{
	auto paragraph = document.GetItem(m_pos)->GetParagraph();
	assert(paragraph);
	paragraph->SetText(m_oldText);
}

void ReplaceTextCommand::Redo(IDocument& document)
{
	auto paragraph = document.GetItem(m_pos)->GetParagraph();
	assert(paragraph);
	paragraph->SetText(m_newText);
}
