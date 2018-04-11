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
		m_storage.SetCopyFlag(m_deletedItem->GetImage()->GetPath(), false);
		m_deleteFlag = true;
	}
}

void DeleteItemCommand::Unexecute(IDocumentCommandControl& control)
{
	control.DoInsertItem(m_deletedItem, m_index);
	if (m_deletedItem->GetImage())
	{
		m_storage.SetCopyFlag(m_deletedItem->GetImage()->GetPath(), true);
		m_deleteFlag = false;
	}
	m_deletedItem = nullptr;
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
