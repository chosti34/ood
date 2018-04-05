#include "stdafx.h"
#include "InsertParagraphCommand.h"
#include "IDocument.h"

InsertParagraphCommand::InsertParagraphCommand(
	const std::string& text, boost::optional<size_t> pos)
	: m_text(text)
	, m_pos(pos)
	, m_insertedAtPos(boost::none)
{
}

bool InsertParagraphCommand::Execute(IDocument& document)
{
	if (m_pos.is_initialized())
	{
		assert(m_pos.value() < document.GetItemsCount());
		m_insertedAtPos = m_pos;
	}
	else
	{
		m_insertedAtPos = document.GetItemsCount();
	}
	auto inserted = document.InsertParagraph(m_text, m_pos);
	assert(inserted != nullptr);
	return true;
}

void InsertParagraphCommand::Undo(IDocument& document)
{
	assert(m_insertedAtPos.is_initialized());
	document.DeleteItem(*m_insertedAtPos);
}

void InsertParagraphCommand::Redo(IDocument& document)
{
	document.InsertParagraph(m_text, m_pos);
}
