#include "stdafx.h"
#include "DeleteItemCommand.h"
#include "ImageFileStorage.h"

DeleteItemCommand::DeleteItemCommand(
	size_t index,
	std::vector<std::shared_ptr<DocumentItem>>& items,
	std::shared_ptr<IImageFileStorage> storage)
	: m_index(index)
	, m_item(nullptr)
	, m_items(items)
	, m_storage(storage)
	, m_deleteImageFlag(false)
{
}

DeleteItemCommand::~DeleteItemCommand()
{
	if (m_deleteImageFlag)
	{
		try
		{
			m_storage->Delete(m_item->GetImage()->GetPath());
		}
		catch (...)
		{
		}
	}
}

void DeleteItemCommand::ExecuteImpl()
{
	m_item = m_items.at(m_index);
	m_items.erase(m_items.begin() + m_index);
	if (m_item->GetImage())
	{
		m_storage->SetCopyFlag(m_item->GetImage()->GetPath(), false);
		m_deleteImageFlag = true;
	}
}

void DeleteItemCommand::UnexecuteImpl()
{
	m_items.insert(m_items.begin() + m_index, m_item);
	if (m_item->GetImage())
	{
		m_storage->SetCopyFlag(m_item->GetImage()->GetPath(), true);
		m_deleteImageFlag = false;
	}
	m_item = nullptr;
}
