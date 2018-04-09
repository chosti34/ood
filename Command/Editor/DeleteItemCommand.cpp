#include "stdafx.h"
#include "DeleteItemCommand.h"

DeleteItemCommand::DeleteItemCommand(size_t index)
	: m_index(index)
	, m_deletedItem(nullptr)
{
}

void DeleteItemCommand::Execute(IDocumentCommandControl& control)
{
	m_deletedItem = control.DoRemoveItem(m_index);
}

void DeleteItemCommand::Unexecute(IDocumentCommandControl& document)
{
	document.DoInsertItem(m_deletedItem, m_index);
	m_deletedItem = nullptr;
}
