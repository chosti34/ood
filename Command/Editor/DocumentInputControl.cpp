#include "stdafx.h"
#include "DocumentInputControl.h"
#include "DocumentSerializer.h"

#include "SetTitleCommand.h"
#include "DeleteItemCommand.h"
#include "ReplaceTextCommand.h"
#include "InsertParagraphCommand.h"

namespace
{
std::vector<std::string> FetchTokens(std::istream& strm)
{
	using namespace std;
	using Iterator = istream_iterator<string>;
	vector<string> tokens;
	copy(Iterator(strm), Iterator(), back_inserter(tokens));
	return tokens;
}

/*
Выбрасывает исключение если прочитать позицию не удалось.
Корректная позиция - либо строка "end", в этом случае будет возвращён none,
либо беззнаковое число.
*/
boost::optional<size_t> ReadAsPosition(const std::string& token)
{
	if (token == "end")
	{
		return boost::none;
	}
	try
	{
		return boost::make_optional<size_t>(stoull(token));
	}
	catch (...)
	{
		throw std::invalid_argument("Invalid position specified");
	}
}

size_t ReadAsIndex(const std::string& token)
{
	try
	{
		return stoull(token);
	}
	catch (...)
	{
		throw std::invalid_argument("Invalid position specified");
	}
}

std::string GetDocumentItemDescription(const DocumentItem& item)
{
	using std::to_string;
	if (item.GetParagraph())
	{
		assert(!item.GetImage());
		return "Paragraph: " + item.GetParagraph()->GetText();
	}
	if (item.GetImage())
	{
		assert(!item.GetParagraph());
		const auto& image = item.GetImage();
		const auto& width = image->GetWidth();
		const auto& height = image->GetHeight();
		const auto& path = image->GetPath();
		return "Image: " + to_string(width) + " " + to_string(height) + " " + path;
	}
	throw std::logic_error("document item is neither image or paragraph");
}
}

DocumentInputControl::DocumentInputControl(IDocument& document, Menu& menu)
	: m_document(document)
	, m_menu(menu)
{
	using std::bind;
	using namespace std::placeholders;
	m_menu.AddItem("Exit", "Exit from menu, no arguments",
		bind(&DocumentInputControl::DoMenuExitCommand, this, _1));
	m_menu.AddItem("Help", "Show commands list, no arguments",
		bind(&DocumentInputControl::DoShowInstructionsCommand, this, _1));
	m_menu.AddItem("SetTitle", "Set title to the document, arguments: <title>",
		bind(&DocumentInputControl::DoSetTitleCommand, this, _1));
	m_menu.AddItem(
		"InsertParagraph",
		"Insert paragraph to the document, arguments: <pos>|end <text>",
		bind(&DocumentInputControl::DoInsertParagraphCommand, this, _1));
	m_menu.AddItem("List", "List all document's elements, no arguments",
		bind(&DocumentInputControl::DoListCommand, this, _1));
	m_menu.AddItem("ReplaceText", "Replace text in paragraph, arguments: <pos> <new text>",
		bind(&DocumentInputControl::DoReplaceTextCommand, this, _1));
	m_menu.AddItem("DeleteItem", "Delete document item, arguments: <pos>",
		bind(&DocumentInputControl::DoDeleteItemCommand, this, _1));
	m_menu.AddItem("Save", "Save html document, arguments: <path>",
		bind(&DocumentInputControl::DoSaveCommand, this, _1));
	m_menu.AddItem("Undo", "Undo last performed operation",
		bind(&DocumentInputControl::DoUndoCommand, this, _1));
	m_menu.AddItem("Redo", "Redo last undoned operation",
		bind(&DocumentInputControl::DoRedoCommand, this, _1));
}

void DocumentInputControl::DoMenuExitCommand(std::istream& /* strm */)
{
	m_menu.Exit();
}

void DocumentInputControl::DoShowInstructionsCommand(std::istream& /* strm */)
{
	m_menu.ShowInstructions();
}

void DocumentInputControl::DoSetTitleCommand(std::istream& strm)
{
	std::string title;
	strm >> title;
	if (!strm)
	{
		std::cout << "Provide title..." << std::endl;
		return;
	}
	m_document.DoCommand(std::make_unique<SetTitleCommand>(title));
}

void DocumentInputControl::DoInsertParagraphCommand(std::istream& strm)
{
	const auto tokens = FetchTokens(strm);
	if (tokens.size() != 2u)
	{
		std::cout << "Expected 2 arguments, " << tokens.size() << " given" << std::endl;
		return;
	}

	const boost::optional<size_t> position = ReadAsPosition(tokens[0]);
	if (!position.is_initialized())
	{
		m_document.DoCommand(std::make_unique<InsertParagraphCommand>(tokens[1]));
	}
	else if (position.value() < m_document.GetItemsCount())
	{
		m_document.DoCommand(std::make_unique<InsertParagraphCommand>(tokens[1], position.value()));
	}
	else
	{
		std::cout << "Index must be less than items count" << std::endl;
	}
}

void DocumentInputControl::DoListCommand(std::istream& /* strm */)
{
	std::cout << "Title: " << m_document.GetTitle() << std::endl;
	for (size_t index = 0u; index < m_document.GetItemsCount(); ++index)
	{
		const auto& item = *m_document.GetItem(index);
		std::cout << index << ". " << GetDocumentItemDescription(item) << std::endl;
	}
}

void DocumentInputControl::DoReplaceTextCommand(std::istream& strm)
{
	const auto tokens = FetchTokens(strm);
	if (tokens.size() != 2u)
	{
		std::cout << "Expected 2 arguments, " << tokens.size() << " given" << std::endl;
		return;
	}

	const size_t index = ReadAsIndex(tokens[0]);
	if (index >= m_document.GetItemsCount())
	{
		std::cout << "Index must be less than items count" << std::endl;
		return;
	}

	if (m_document.GetItem(index)->GetParagraph())
	{
		assert(!m_document.GetItem(index)->GetImage());
		m_document.DoCommand(std::make_unique<ReplaceTextCommand>(index, tokens[1]));
	}
	else
	{
		std::cout << "Element at specified index is not a paragraph" << std::endl;
	}
}

void DocumentInputControl::DoDeleteItemCommand(std::istream& strm)
{
	size_t index = 0u;
	strm >> index;
	if (!strm)
	{
		std::cout << "Invalid index specified" << std::endl;
		return;
	}

	if (index >= m_document.GetItemsCount())
	{
		std::cout << "Index must be less than items count" << std::endl;
		return;
	}

	m_document.DoCommand(std::make_unique<DeleteItemCommand>(index));
}

void DocumentInputControl::DoSaveCommand(std::istream& strm)
{
	std::string path;
	strm >> path;
	if (!strm)
	{
		std::cout << "Provide path..." << std::endl;
		return;
	}

	try
	{
		DocumentSerializer serializer;
		serializer.SerializeAsHTML(path, m_document);
	}
	catch (...)
	{
		std::cout << "Failed to save document... Try again later" << std::endl;
	}
}

void DocumentInputControl::DoUndoCommand(std::istream& /* strm */)
{
	if (m_document.CanUndo())
	{
		m_document.Undo();
	}
	else
	{
		std::cout << "Can't undo" << std::endl;
	}
}

void DocumentInputControl::DoRedoCommand(std::istream& /* strm */)
{
	if (m_document.CanRedo())
	{
		m_document.Redo();
	}
	else
	{
		std::cout << "Can't redo" << std::endl;
	}
}
