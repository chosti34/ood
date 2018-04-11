#include "stdafx.h"
#include "InsertImageCommand.h"
#include "Image.h"
#include "ImageFileStorage.h"

InsertImageCommand::InsertImageCommand(
	unsigned width, unsigned height,
	const std::string& path, boost::optional<size_t> position,
	ImageFileStorage& storage)
	: m_width(width)
	, m_height(height)
	, m_path(path)
	, m_position(position)
	, m_storage(storage)
	, m_deleteFlag(true)
{
}

void InsertImageCommand::Execute(IDocumentCommandControl& control)
{
	auto item = std::make_shared<DocumentItem>(nullptr, std::make_shared<Image>(m_path, m_width, m_height));
	control.DoInsertItem(item, m_position);
	m_deleteFlag = false;
	m_storage.SetCopyFlag(m_path, true);
}

void InsertImageCommand::Unexecute(IDocumentCommandControl& control)
{
	control.DoRemoveItem(m_position);
	m_deleteFlag = true;
	m_storage.SetCopyFlag(m_path, false);
}

InsertImageCommand::~InsertImageCommand()
{
	if (m_deleteFlag)
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
