#include "stdafx.h"
#include "Image.h"
#include "DocumentItem.h"
#include "InsertImageCommand.h"
#include "ImageFileStorage.h"

InsertImageCommand::InsertImageCommand(
	IDocumentCommandControl& control,
	ICommandManager& manager,
	unsigned width, unsigned height,
	const std::string& path,
	boost::optional<size_t> position,
	IImageFileStorage& storage)
	: m_width(width)
	, m_height(height)
	, m_path(path)
	, m_position(position)
	, m_storage(storage)
	, m_control(control)
	, m_manager(manager)
	, m_item(nullptr)
{
}

InsertImageCommand::~InsertImageCommand()
{
	if (IsExecuted())
	{
		try
		{
			m_storage.Delete(m_path);
		}
		catch (...)
		{
		}
	}
}

void InsertImageCommand::ExecuteImpl()
{
	if (!m_item)
	{
		m_item = std::make_shared<DocumentItem>(nullptr, std::make_shared<Image>(m_path, m_width, m_height), m_manager);
	}
	m_control.DoInsertItem(m_item, m_position);
	m_storage.SetCopyFlag(m_path, true);
}

void InsertImageCommand::UnexecuteImpl()
{
	m_item = m_control.DoRemoveItem(m_position);
	m_storage.SetCopyFlag(m_path, false);
}
