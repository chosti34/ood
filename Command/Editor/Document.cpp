#include "stdafx.h"
#include "Document.h"
#include "Image.h"
#include "Paragraph.h"
#include "CommandManager.h"
#include "ChangeStringCommand.h"
#include "DeleteItemCommand.h"
#include "ReplaceTextCommand.h"
#include "ResizeImageCommand.h"
#include "InsertParagraphCommand.h"
#include "InsertImageCommand.h"
#include "ImageFileStorage.h"
#include "AbstractDocumentSerializer.h"

namespace
{
constexpr unsigned COMMAND_HISTORY_DEPTH = 10u;
}

Document::Document(const std::string& title, std::shared_ptr<IImageFileStorage> storage)
	: m_title(title)
	, m_items()
	, m_commandManager(std::make_unique<CommandManager>(COMMAND_HISTORY_DEPTH))
	, m_storage(storage)
{
}

void Document::InsertParagraph(const std::string& text, boost::optional<size_t> position)
{
	if (position && *position >= m_items.size())
	{
		throw std::out_of_range("position must be less than items count");
	}

	auto paragraph = std::make_shared<Paragraph>(text, *m_commandManager);
	m_commandManager->ApplyCommand(std::make_unique<InsertParagraphCommand>(position, paragraph, m_items));
}

void Document::InsertImage(const std::string& path, unsigned width, unsigned height, boost::optional<size_t> position)
{
	if (position && *position >= m_items.size())
	{
		throw std::out_of_range("position must be less than items count");
	}

	const std::string insertedImagePath = m_storage->AddImage(path);
	auto image = std::make_shared<Image>(insertedImagePath, width, height, *m_commandManager);

	m_commandManager->ApplyCommand(std::make_unique<InsertImageCommand>(position, image, m_items, m_storage));
}

void Document::RemoveItem(size_t index)
{
	if (index >= m_items.size())
	{
		throw std::invalid_argument("index must be less than items count");
	}
	m_commandManager->ApplyCommand(std::make_unique<DeleteItemCommand>(index, m_items, m_storage));
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
	m_items[index]->GetParagraph()->SetText(text);
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
	m_items[index]->GetImage()->Resize(width, height);
}

void Document::SetTitle(const std::string& title)
{
	m_commandManager->ApplyCommand(std::make_unique<ChangeStringCommand>(m_title, title));
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
	return m_commandManager->CanUndo();
}

void Document::Undo()
{
	assert(m_commandManager->CanUndo());
	m_commandManager->Undo();
}

bool Document::CanRedo()const
{
	return m_commandManager->CanRedo();
}

void Document::Redo()
{
	assert(m_commandManager->CanRedo());
	m_commandManager->Redo();
}

void Document::Save(const std::string& path)
{
	m_storage->CopyTo(path);

	auto serializer = CreateSerializer(path);
	serializer->SetTitle(m_title);

	for (const auto& item : m_items)
	{
		const auto& paragraph = item->GetParagraph();
		const auto& image = item->GetImage();
		if (paragraph)
		{
			serializer->InsertParagraph(paragraph->GetText());
		}
		if (image)
		{
			serializer->InsertImage(image->GetPath(), image->GetWidth(), image->GetHeight());
		}
	}

	serializer->Serialize(path);
}
