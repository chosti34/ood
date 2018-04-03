#include "stdafx.h"
#include "Document.h"

Document::Document(const std::string& title)
	: m_title(title)
{
}

void Document::OnCommand(std::unique_ptr<IDocumentCommand> && command)
{
	if (command->Execute(*this))
	{
	}
}

std::shared_ptr<IParagraph> Document::InsertParagraph(const std::string& text, boost::optional<size_t> position)
{
	(void)text;
	(void)position;
	return std::shared_ptr<IParagraph>();
}

std::shared_ptr<IImage> Document::InsertImage(const Path& path, int width, int height, boost::optional<size_t> position)
{
	(void)path;
	(void)width;
	(void)height;
	(void)position;
	return std::shared_ptr<IImage>();
}

size_t Document::GetItemsCount()const
{
	return size_t();
}

CConstDocumentItem Document::GetItem(size_t index)const
{
	(void)index;
	return CConstDocumentItem();
}

CDocumentItem Document::GetItem(size_t index)
{
	(void)index;
	return CDocumentItem();
}

void Document::DeleteItem(size_t index)
{
	(void)index;
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
	return false;
}

void Document::Undo()
{
}

bool Document::CanRedo()const
{
	return false;
}

void Document::Redo()
{
}

void Document::Save(const Path& path)const
{
	(void)path;
}
