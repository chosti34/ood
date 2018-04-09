#include "stdafx.h"
#include "Document.h"
#include "SetTitleCommand.h"
#include "DeleteItemCommand.h"
#include "ReplaceTextCommand.h"
#include "InsertParagraphCommand.h"

namespace
{
constexpr unsigned COMMAND_HISTORY_DEPTH = 10u;
const std::string DOCUMENT_TITLE = "untitled";
}

Document::Document()
	: Document(DOCUMENT_TITLE)
{
}

Document::Document(const std::string& title)
	: m_title(title)
	, m_commandManager(COMMAND_HISTORY_DEPTH)
	, m_items()
{
}

void Document::InsertParagraph(const std::string& text, boost::optional<size_t> position)
{
	if (position && *position >= m_items.size())
	{
		throw std::invalid_argument("invalid position specified");
	}
	DoCommand<InsertParagraphCommand>(text, position);
}

void Document::InsertImage(const std::string& path, unsigned width, unsigned height, boost::optional<size_t> position)
{
	// TODO: implement this
}

void Document::RemoveItem(size_t index)
{
	if (index >= m_items.size())
	{
		throw std::invalid_argument("invalid index specified");
	}
	DoCommand<DeleteItemCommand>(index);
}

void Document::ReplaceText(const std::string& text, size_t index)
{
	if (index >= m_items.size())
	{
		throw std::invalid_argument("invalid index specified");
	}
	auto paragraph = m_items[index]->GetParagraph();
	if (!paragraph)
	{
		throw std::invalid_argument("item at specified index is not a paragraph");
	}
	DoCommand<ReplaceTextCommand>(text, paragraph->GetText(), index);
}

void Document::ResizeImage(unsigned width, unsigned height, size_t index)
{
	// TODO: implement this
}

void Document::SetTitle(const std::string& title)
{
	DoCommand<SetTitleCommand>(title, m_title);
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
	throw std::out_of_range("invalid index");
}

std::shared_ptr<const DocumentItem> Document::GetItem(size_t index)const
{
	if (index < m_items.size())
	{
		return m_items[index];
	}
	throw std::out_of_range("invalid index");
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

void Document::DoInsertItem(const std::shared_ptr<DocumentItem>& item, boost::optional<size_t> position)
{
	if (!position)
	{
		m_items.push_back(item);
		return;
	}
	assert(*position < m_items.size());
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

void Document::DoReplaceText(const std::string& text, size_t index)
{
	assert(index < m_items.size());
	assert(m_items[index]->GetParagraph());
	m_items[index]->GetParagraph()->SetText(text);
}

void Document::DoResizeImage(unsigned width, unsigned height, size_t index)
{
	// TODO: implement this
}
