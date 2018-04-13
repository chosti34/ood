#include "stdafx.h"
#include "DeleteItemCommand.h"
#include "ImageFileStorage.h"

DeleteItemCommand::DeleteItemCommand(
	IDocumentCommandControl& control,
	boost::optional<size_t> index,
	IImageFileStorage& storage)
	: m_index(index)
	, m_deletedItem(nullptr)
	, m_storage(storage)
	, m_imageDeletedFlag(false)
	, m_control(control)
{
}

DeleteItemCommand::~DeleteItemCommand()
{
	if (m_imageDeletedFlag)
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

void DeleteItemCommand::ExecuteImpl()
{
	m_deletedItem = m_control.DoRemoveItem(m_index);
	if (m_deletedItem->GetImage())
	{
		m_storage.SetCopyFlag(m_deletedItem->GetImage()->GetPath(), false);
		m_imageDeletedFlag = true;
	}
}

void DeleteItemCommand::UnexecuteImpl()
{
	m_control.DoInsertItem(m_deletedItem, m_index);
	if (m_deletedItem->GetImage())
	{
		m_storage.SetCopyFlag(m_deletedItem->GetImage()->GetPath(), true);
		m_imageDeletedFlag = false;
	}
	m_deletedItem = nullptr;
}
