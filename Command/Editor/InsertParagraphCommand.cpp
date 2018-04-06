#include "stdafx.h"
#include "InsertParagraphCommand.h"
#include "Paragraph.h"

InsertParagraphCommand::InsertParagraphCommand(const std::string& text, boost::optional<size_t> index)
	: m_text(text)
	, m_index(index)
{
}

void InsertParagraphCommand::Execute(IDocumentControl& document)
{
	auto item = std::make_shared<DocumentItem>(std::make_shared<Paragraph>(m_text), nullptr);
	document.DoInsertItem(item, m_index);
}

void InsertParagraphCommand::Unexecute(IDocumentControl& document)
{
	document.DoRemoveItem(m_index);
}
