#include "stdafx.h"
#include "InsertParagraphCommand.h"
#include "Paragraph.h"

InsertParagraphCommand::InsertParagraphCommand(
	boost::optional<size_t> index,
	const std::shared_ptr<IParagraph>& paragraph,
	std::vector<std::shared_ptr<DocumentItem>>& items)
	: m_index(index)
	, m_item(std::make_shared<DocumentItem>(paragraph, nullptr))
	, m_items(items)
{
}

void InsertParagraphCommand::ExecuteImpl()
{
	if (m_index)
	{
		m_items.insert(m_items.begin() + *m_index, m_item);
	}
	else
	{
		m_items.push_back(m_item);
	}
}

void InsertParagraphCommand::UnexecuteImpl()
{
	if (m_index)
	{
		m_items.erase(m_items.begin() + *m_index);
	}
	else
	{
		m_items.pop_back();
	}
}
