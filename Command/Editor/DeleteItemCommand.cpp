#include "stdafx.h"
#include "DeleteItemCommand.h"
#include "IDocument.h"

DeleteItemCommand::DeleteItemCommand(size_t pos)
	: m_pos(pos)
	, m_deletedItem(nullptr)
{
}

bool DeleteItemCommand::Execute(IDocument& document)
{
	if (m_pos < document.GetItemsCount())
	{
		m_deletedItem = document.GetItem(m_pos);
		document.DeleteItem(m_pos);
		return true;
	}
	return false;
}

void DeleteItemCommand::Undo(IDocument& document)
{
	if (m_deletedItem->GetImage())
	{
		assert(!m_deletedItem->GetParagraph());
		const auto& image = m_deletedItem->GetImage();
		document.InsertImage(image->GetPath(), image->GetWidth(), image->GetHeight(), m_pos);
	}
	if (m_deletedItem->GetParagraph())
	{
		assert(!m_deletedItem->GetImage());
		const auto& paragraph = m_deletedItem->GetParagraph();
		document.InsertParagraph(paragraph->GetText(), m_pos);
	}
}

void DeleteItemCommand::Redo(IDocument& document)
{
	bool executed = Execute(document);
	assert(executed);
}
