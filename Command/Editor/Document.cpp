#include "stdafx.h"
#include "Document.h"
#include "Paragraph.h"

namespace
{
const unsigned COMMAND_HISTORY_DEPTH = 10u;
}

Document::Document()
	: m_title("untitled")
	, m_items()
	, m_commandManager(COMMAND_HISTORY_DEPTH)
{
}

bool Document::DoCommand(IDocumentCommandPtr&& command)
{
	if (command->Execute(*this))
	{
		m_commandManager.RegisterCommand(std::move(command));
		return true;
	}
	return false;
}

std::shared_ptr<IParagraph> Document::InsertParagraph(
	const std::string& text, boost::optional<size_t> position)
{
	auto docItem = std::make_shared<DocumentItem>(std::make_shared<Paragraph>(text), nullptr);
	if (position.is_initialized())
	{
		m_items.insert(m_items.begin() + position.value(), docItem);
	}
	else
	{
		m_items.push_back(docItem);
	}
	return docItem->GetParagraph();
}

std::shared_ptr<IImage> Document::InsertImage(
	const std::string& path, int width, int height, boost::optional<size_t> position)
{
	(void)path;
	(void)width;
	(void)height;
	(void)position;
	return std::shared_ptr<IImage>();
}

size_t Document::GetItemsCount()const
{
	return m_items.size();
}

std::shared_ptr<DocumentItem> Document::GetItem(size_t index)
{
	if (index < m_items.size())
	{
		return m_items[index];
	}
	throw std::out_of_range(
		"index is " + std::to_string(index) + " when size is " + std::to_string(m_items.size()));
}

std::shared_ptr<const DocumentItem> Document::GetItem(size_t index)const
{
	if (index < m_items.size())
	{
		return m_items[index];
	}
	throw std::out_of_range(
		"index is " + std::to_string(index) + " when size is " + std::to_string(m_items.size()));
}

void Document::DeleteItem(size_t index)
{
	m_items.erase(m_items.begin() + index);
}

std::string Document::GetTitle()const
{
	return m_title;
}

void Document::SetTitle(const std::string& title)
{
	m_title = title;
}

bool Document::CanUndo()const
{
	return m_commandManager.CanUndo();
}

void Document::Undo()
{
	assert(m_commandManager.CanUndo());
	m_commandManager.Undo(*this);
}

bool Document::CanRedo()const
{
	return m_commandManager.CanRedo();
}

void Document::Redo()
{
	assert(m_commandManager.CanRedo());
	m_commandManager.Redo(*this);
}
