#include "stdafx.h"
#include "DeleteItemCommand.h"
#include "ImageFileStorage.h"

DeleteItemCommand::DeleteItemCommand(size_t index, ImageFileStorage& storage)
	: m_index(index)
	, m_deletedItem(nullptr)
	, m_storage(storage)
	, m_deleteFlag(false)
{
}

void DeleteItemCommand::Execute(IDocumentCommandControl& control)
{
	m_deletedItem = control.DoRemoveItem(m_index);
	if (m_deletedItem->GetImage())
	{
		m_deleteFlag = true;
	}
}

void DeleteItemCommand::Unexecute(IDocumentCommandControl& control)
{
	control.DoInsertItem(m_deletedItem, m_index);
	m_deletedItem = nullptr;
	m_deleteFlag = false;
}

DeleteItemCommand::~DeleteItemCommand()
{
	if (m_deleteFlag)
	{
		assert(m_deletedItem);
		assert(m_deletedItem->GetImage());
		try
		{
			m_storage.Delete(m_deletedItem->GetImage()->GetPath());
		}
		catch (...)
		{
		}
	}
}
