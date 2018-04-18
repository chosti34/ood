#include "stdafx.h"
#include "Image.h"
#include "DocumentItem.h"
#include "InsertImageCommand.h"
#include "ImageFileStorage.h"

InsertImageCommand::InsertImageCommand(
	boost::optional<size_t> index,
	std::shared_ptr<IImage> image,
	std::vector<std::shared_ptr<DocumentItem>>& items,
	std::shared_ptr<IImageFileStorage> storage)
	: m_index(index)
	, m_item(std::make_shared<DocumentItem>(nullptr, image))
	, m_items(items)
	, m_storage(storage)
{
}

InsertImageCommand::~InsertImageCommand()
{
	if (!IsExecuted())
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

void InsertImageCommand::ExecuteImpl()
{
	if (m_index)
	{
		m_items.insert(m_items.begin() + *m_index, m_item);
	}
	else
	{
		m_items.push_back(m_item);
	}
	m_storage->SetCopyFlag(m_item->GetImage()->GetPath(), true);
}

void InsertImageCommand::UnexecuteImpl()
{
	if (m_index)
	{
		m_items.erase(m_items.begin() + *m_index);
	}
	else
	{
		m_items.pop_back();
	}
	m_storage->SetCopyFlag(m_item->GetImage()->GetPath(), false);
}
