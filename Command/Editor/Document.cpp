#include "stdafx.h"
#include "Document.h"
#include "SetTitleCommand.h"
#include "DeleteItemCommand.h"
#include "ReplaceTextCommand.h"
#include "ResizeImageCommand.h"
#include "InsertParagraphCommand.h"
#include "InsertImageCommand.h"
#include "ImageFileStorage.h"

namespace
{
constexpr unsigned COMMAND_HISTORY_DEPTH = 10u;
const std::string DOCUMENT_TITLE = "untitled";
}

Document::Document(IImageFileStorage& storage)
	: Document(storage, DOCUMENT_TITLE)
{
}

Document::Document(IImageFileStorage& storage, const std::string& title)
	: m_title(title)
	, m_commandManager(COMMAND_HISTORY_DEPTH)
	, m_items()
	, m_storage(storage)
{
}

void Document::InsertParagraph(const std::string& text, boost::optional<size_t> position)
{
	if (position && *position >= m_items.size())
	{
		throw std::out_of_range("position must be less than items count");
	}
	auto command = std::unique_ptr<InsertParagraphCommand>(new InsertParagraphCommand(*this, m_commandManager, text, position));
	command->Execute();
	m_commandManager.RegisterCommand(std::move(command));
}

void Document::InsertImage(const std::string& path, unsigned width, unsigned height, boost::optional<size_t> position)
{
	if (position && *position >= m_items.size())
	{
		throw std::out_of_range("position must be less than items count");
	}
	const std::string insertedImagePath = m_storage.AddImage(path);
	auto command = std::unique_ptr<InsertImageCommand>(
		new InsertImageCommand(*this, m_commandManager, width, height, insertedImagePath, position, m_storage));
	command->Execute();
	m_commandManager.RegisterCommand(std::move(command));
}

void Document::RemoveItem(size_t index)
{
	if (index >= m_items.size())
	{
		throw std::invalid_argument("index must be less than items count");
	}
	const auto position = index == (m_items.size() - 1) ? boost::none : boost::make_optional(index);
	auto command = std::unique_ptr<DeleteItemCommand>(new DeleteItemCommand(*this, index, m_storage));
	command->Execute();
	m_commandManager.RegisterCommand(std::move(command));
}

void Document::ReplaceText(const std::string& text, size_t index)
{
	if (index >= m_items.size())
	{
		throw std::invalid_argument("index must be less than items count");
	}
	if (!m_items[index]->GetParagraph())
	{
		throw std::invalid_argument("item at specified index is not a paragraph");
	}
	m_items[index]->ReplaceText(text);
}

void Document::ResizeImage(unsigned width, unsigned height, size_t index)
{
	if (index >= m_items.size())
	{
		throw std::invalid_argument("index must be less than items count");
	}
	if (!m_items[index]->GetImage())
	{
		throw std::invalid_argument("item at specified index is not a paragraph");
	}
	m_items[index]->ResizeImage(width, height);
}

void Document::SetTitle(const std::string& title)
{
	auto command = std::unique_ptr<SetTitleCommand>(new SetTitleCommand(*this, title, m_title));
	command->Execute();
	m_commandManager.RegisterCommand(std::move(command));
}

std::string Document::GetTitle()const
{
	return m_title;
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
	throw std::out_of_range("index must be less than items count");
}

std::shared_ptr<const DocumentItem> Document::GetItem(size_t index)const
{
	if (index < m_items.size())
	{
		return m_items[index];
	}
	throw std::out_of_range("index must be less than items count");
}

bool Document::CanUndo()const
{
	return m_commandManager.CanUndo();
}

void Document::Undo()
{
	assert(m_commandManager.CanUndo());
	m_commandManager.Undo();
}

bool Document::CanRedo()const
{
	return m_commandManager.CanRedo();
}

void Document::Redo()
{
	assert(m_commandManager.CanRedo());
	m_commandManager.Redo();
}

void Document::DoInsertItem(const std::shared_ptr<DocumentItem>& item, boost::optional<size_t> position)
{
	if (!position)
	{
		m_items.push_back(item);
		return;
	}
	assert(*position < m_items.size() || *position == 0);
	m_items.insert(m_items.begin() + *position, item);
}

std::shared_ptr<DocumentItem> Document::DoRemoveItem(boost::optional<size_t> position)
{
	if (!position)
	{
		assert(!m_items.empty());
		auto item = m_items.back();
		m_items.pop_back();
		return item;
	}
	assert(*position < m_items.size());
	auto item = m_items[*position];
	m_items.erase(m_items.begin() + *position);
	return item;
}

void Document::DoSetTitle(const std::string& title)
{
	m_title = title;
}
