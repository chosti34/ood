#include "stdafx.h"
#include "InsertParagraphCommand.h"
#include "Paragraph.h"

InsertParagraphCommand::InsertParagraphCommand(
	IDocumentCommandControl& control,
	ICommandManager& manager,
	const std::string& text,
	boost::optional<size_t> position)
	: m_control(control)
	, m_manager(manager)
	, m_text(text)
	, m_position(position)
{
}

void InsertParagraphCommand::ExecuteImpl()
{
	if (!m_item)
	{
		m_item = std::make_shared<DocumentItem>(std::make_shared<Paragraph>(m_text), nullptr, m_manager);
	}
	m_control.DoInsertItem(m_item, m_position);
}

void InsertParagraphCommand::UnexecuteImpl()
{
	m_item = m_control.DoRemoveItem(m_position);
}
