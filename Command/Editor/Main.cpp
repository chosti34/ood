#include "stdafx.h"
#include "Menu.h"
#include "Document.h"
#include "HtmlExport.h"

#include "SetTitleCommand.h"
#include "DeleteItemCommand.h"
#include "ReplaceTextCommand.h"
#include "InsertParagraphCommand.h"

namespace
{
bool ParseNumber(const std::string& str, uint64_t& num)
{
	try
	{
		num = stoull(str);
	}
	catch (const std::exception& ex)
	{
		(void)ex;
		return false;
	}
	return true;
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

class MenuCommandsBinder
{
public:
	MenuCommandsBinder(Menu& menu, Document& document)
		: m_menu(menu)
		, m_document(document)
	{
		using std::bind;
		using namespace std::placeholders;
		m_menu.AddItem("Exit", "Exit from menu, no arguments",
			bind(&MenuCommandsBinder::OnMenuExit, this, _1));
		m_menu.AddItem("Help", "Show commands list, no arguments",
			bind(&MenuCommandsBinder::OnShowInstructions, this, _1));
		m_menu.AddItem("SetTitle", "Set title to the document, arguments: <title>",
			bind(&MenuCommandsBinder::OnSetTitleCommand, this, _1));
		m_menu.AddItem(
			"InsertParagraph",
			"Insert paragraph to the document, arguments: <pos>|end <text>",
			bind(&MenuCommandsBinder::OnInsertParagraphCommand, this, _1));
		m_menu.AddItem("List", "List all document's elements, no arguments",
			bind(&MenuCommandsBinder::OnListCommand, this, _1));
		m_menu.AddItem("ReplaceText", "Replace text in paragraph, arguments: <pos> <new text>",
			bind(&MenuCommandsBinder::OnReplaceTextCommand, this, _1));
		m_menu.AddItem("DeleteItem", "Delete document item, arguments: <pos>",
			bind(&MenuCommandsBinder::OnDeleteItem, this, _1));
		m_menu.AddItem("Save", "Save html document, arguments: <path>",
			bind(&MenuCommandsBinder::OnSave, this, _1));
		m_menu.AddItem("Undo", "Undo last performed operation",
			bind(&MenuCommandsBinder::OnUndo, this, _1));
		m_menu.AddItem("Redo", "Redo last undoned operation",
			bind(&MenuCommandsBinder::OnRedo, this, _1));
	}

private:
	void OnMenuExit(const std::vector<std::string>& args)
	{
		if (!args.empty())
		{
			std::cout << "Expected no arguments, " << args.size() << " given\n";
			return;
		}
		m_menu.Exit();
	}

	void OnShowInstructions(const std::vector<std::string>& args)
	{
		if (!args.empty())
		{
			std::cout << "Expected no arguments, " << args.size() << " given\n";
			return;
		}
		m_menu.ShowInstructions();
	}

	void OnSetTitleCommand(const std::vector<std::string>& args)
	{
		if (args.size() != 1u)
		{
			std::cout << "Expected 1 argument, " << args.size() << " given\n";
			return;
		}
		m_document.DoCommand(std::make_unique<SetTitleCommand>(args[0]));
	}

	void OnInsertParagraphCommand(const std::vector<std::string>& args)
	{
		if (args.size() != 2u)
		{
			std::cout << "Expected 2 arguments, " << args.size() << " given\n";
			return;
		}
		if (args[0] == "end")
		{
			m_document.DoCommand(std::make_unique<InsertParagraphCommand>(args[1]));
		}
		else
		{
			size_t pos = 0;
			if (ParseNumber(args[0], pos) && pos < m_document.GetItemsCount())
			{
				m_document.DoCommand(std::make_unique<InsertParagraphCommand>(args[1], pos));
			}
			else
			{
				std::cout << "Invalid position specified\n";
			}
		}
	}

	void OnListCommand(const std::vector<std::string>& args)
	{
		if (!args.empty())
		{
			std::cout << "Expected no arguments, " << args.size() << " given\n";
			return;
		}
		
		std::cout << "Title: " << m_document.GetTitle() << std::endl;
		for (size_t index = 0u; index < m_document.GetItemsCount(); ++index)
		{
			const auto& item = *m_document.GetItem(index);
			std::cout << index << ". " << GetDocumentItemDescription(item) << std::endl;
		}
	}

	void OnReplaceTextCommand(const std::vector<std::string>& args)
	{
		if (args.size() != 2u)
		{
			std::cout << "Expected 2 arguments, " << args.size() << " given\n";
			return;
		}
		size_t pos = 0;
		if (ParseNumber(args[0], pos) && pos < m_document.GetItemsCount())
		{
			if (m_document.GetItem(pos)->GetParagraph() != nullptr)
			{
				assert(m_document.GetItem(pos)->GetImage() == nullptr);
				m_document.DoCommand(std::make_unique<ReplaceTextCommand>(pos, args[1]));
			}
			else
			{
				std::cout << "Element at specified position is not a paragraph\n";
			}
			return;
		}
		std::cout << "Invalid position specified\n";
	}

	void OnDeleteItem(const std::vector<std::string>& args)
	{
		if (args.size() != 1u)
		{
			std::cout << "Expected 1 argument, " << args.size() << " given\n";
			return;
		}
		size_t pos = 0u;
		if (ParseNumber(args[0], pos) && pos < m_document.GetItemsCount())
		{
			m_document.DoCommand(std::make_unique<DeleteItemCommand>(pos));
			return;
		}
	}

	void OnSave(const std::vector<std::string>& args)
	{
		if (args.size() != 1u)
		{
			std::cout << "Expected 1 argument, " << args.size() << " given\n";
			return;
		}
		const std::string& path = args.front();
		try
		{
			ExportAsHtmlDocument(path, m_document);
		}
		catch (const std::exception& ex)
		{
			std::cout << "Error: " << ex.what() << std::endl;
		}
	}

	void OnUndo(const std::vector<std::string>& args)
	{
		if (!args.empty())
		{
			std::cout << "Expected no arguments, " << args.size() << " given\n";
			return;
		}
		if (m_document.CanUndo())
		{
			m_document.Undo();
		}
		else
		{
			std::cout << "Can't undo" << std::endl;
		}
	}

	void OnRedo(const std::vector<std::string>& args)
	{
		if (!args.empty())
		{
			std::cout << "Expected no arguments, " << args.size() << " given\n";
			return;
		}
		if (m_document.CanRedo())
		{
			m_document.Redo();
		}
		else
		{
			std::cout << "Can't redo" << std::endl;
		}
	}

private:
	Menu& m_menu;
	Document& m_document;
};
}

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	try
	{
		Menu menu;
		Document document;
		MenuCommandsBinder binder(menu, document);
		menu.Run();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
