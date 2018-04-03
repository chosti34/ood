#include "stdafx.h"
#include "Document.h"

void Document::OnCommand(std::unique_ptr<ICommand>&& command)
{
}

std::shared_ptr<IParagraph> Document::InsertParagraph(const std::string & text, boost::optional<size_t> position)
{
	return std::shared_ptr<IParagraph>();
}

std::shared_ptr<IImage> Document::InsertImage(const Path & path, int width, int height, boost::optional<size_t> position)
{
	return std::shared_ptr<IImage>();
}

size_t Document::GetItemsCount() const
{
	return size_t();
}

CConstDocumentItem Document::GetItem(size_t index) const
{
	return CConstDocumentItem();
}

CDocumentItem Document::GetItem(size_t index)
{
	return CDocumentItem();
}

void Document::DeleteItem(size_t index)
{
}

std::string Document::GetTitle() const
{
	return std::string();
}

void Document::SetTitle(const std::string & title)
{
}

bool Document::CanUndo() const
{
	return false;
}

void Document::Undo()
{
}

bool Document::CanRedo() const
{
	return false;
}

void Document::Redo()
{
}

void Document::Save(const Path & path) const
{
}
