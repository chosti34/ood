#include "stdafx.h"
#include "Document.h"
#include "SetTitleCommand.h"
#include "InsertParagraphCommand.h"
#include "Menu.h"

using namespace std;

namespace
{
std::vector<std::string> Tokenize(std::istream& strm)
{
	std::vector<std::string> tokens;
	std::string token;
	while (strm >> token)
	{
		tokens.emplace_back(std::move(token));
	}
	return tokens;
}

class MenuCommandBinder
{
public:
	MenuCommandBinder(Menu& menu, Document& document)
		: m_menu(menu)
		, m_document(document)
	{
		using namespace std::placeholders;
		using std::bind;
		m_menu.AddItem("Exit", "Exit from menu", bind(&MenuCommandBinder::OnMenuExit, this, _1));
		m_menu.AddItem("Help", "Show menu instructions", bind(&MenuCommandBinder::OnMenuHelp, this, _1));
		m_menu.AddItem("SetTitle", "Set title to the document", bind(&MenuCommandBinder::OnDocumentSetTitle, this, _1));
		m_menu.AddItem("InsertParagraph", "Insert paragraph to the document", bind(&MenuCommandBinder::OnInsertParagraph, this, _1));
	}

private:
	void OnMenuExit(std::istream& strm)
	{
		(void)strm;
		m_menu.Exit();
	}

	void OnMenuHelp(std::istream& strm)
	{
		(void)strm;
		m_menu.ShowInstructions();
	}

	void OnDocumentSetTitle(std::istream& strm)
	{
		std::string title;
		if (strm >> title)
		{
			m_document.OnCommand(std::make_unique<SetTitleCommand>(title));
		}
		else
		{
			std::cout << "Please, provide title...\n";
		}
	}

	void OnInsertParagraph(std::istream& strm)
	{
		std::string token;
		auto args = Tokenize(strm);
		if (args.size() == 2u)
		{
			if (args[0] == "end")
			{
				m_document.OnCommand(make_unique<InsertParagraphCommand>(args[1]));
			}
			else
			{
				m_document.OnCommand(make_unique<InsertParagraphCommand>(args[1], stoul(args[0])));
			}
		}
		else
		{
			std::cout << "Please, provide position and text...\n";
		}
	}

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
		Document document("hello");
		MenuCommandBinder binder(menu, document);
		menu.Run();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
