#include "stdafx.h"
#include "InsertParagraphCommand.h"

InsertParagraphCommand::InsertParagraphCommand(const std::string& text, boost::optional<size_t> position)
	: m_text(text)
	, m_position(position)
{
}

bool InsertParagraphCommand::Execute(IDocument& document)
{
	return false;
}

void InsertParagraphCommand::Undo(IDocument& document)
{
}

void InsertParagraphCommand::Redo(IDocument& document)
{
}
