#include "stdafx.h"
#include "InsertParagraphCommand.h"
#include "Paragraph.h"

InsertParagraphCommand::InsertParagraphCommand(const std::string& text, boost::optional<size_t> position)
	: m_text(text)
	, m_position(position)
{
}

void InsertParagraphCommand::Execute(IDocumentCommandControl& document)
{
	auto item = std::make_shared<DocumentItem>(std::make_shared<Paragraph>(m_text), nullptr);
	document.DoInsertItem(item, m_position);
}

void InsertParagraphCommand::Unexecute(IDocumentCommandControl& document)
{
	document.DoRemoveItem(m_position);
}
