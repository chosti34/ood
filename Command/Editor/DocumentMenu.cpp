#include "stdafx.h"
#include "DocumentMenu.h"

namespace
{
// В случае "end" -> boost::none
// иначе попытка считать как optional<size_t>
boost::optional<size_t> ReadAsDocumentPosition(const std::string& str)
{
	if (str == "end")
	{
		return boost::none;
	}

	size_t position;
	if (sscanf_s(str.c_str(), "%zu", &position) == 1)
	{
		return boost::optional<size_t>(position);
	}
	throw std::invalid_argument("can't reinterpret " + str + " as document's position");
}

size_t ReadAsIndex(const std::string& str)
{
	size_t index;
	if (sscanf_s(str.c_str(), "%zu", &index) == 1)
	{
		return index;
	}
	throw std::invalid_argument("can't read " + str + " as index");
}

unsigned ReadAsUnsigned(const std::string& str)
{
	unsigned number;
	if (sscanf_s(str.c_str(), "%u", &number) == 1)
	{
		return number;
	}
	throw std::invalid_argument("can't read " + str + " as unsigned");
}
}

DocumentMenu::DocumentMenu(std::istream& input, std::ostream& output, IDocument& document)
	: m_document(document)
	, Menu(input, output)
{
	using std::bind;
	using namespace std::placeholders;
	AddItem("Exit", "Exit from menu, no args", [this](auto const&) { Exit(); });
	AddItem("Help", "Show command instructions, no args",
		[this](auto const&) { ShowInstructions(); });
	AddItem("SetTitle", "Set document title, args: <title>",
		bind(&DocumentMenu::SetDocumentTitle, this, _1));
	AddItem("InsertParagraph", "Insert paragraph, args: <pos>|end <text>",
		bind(&DocumentMenu::InsertParagraph, this, _1));
	AddItem("InsertImage", "Insert image, args: <pos>|end <width> <height> <path>",
		bind(&DocumentMenu::InsertImage, this, _1));
	AddItem("List", "List all document's elements, no args",
		bind(&DocumentMenu::List, this, _1));
	AddItem("ReplaceText", "Replace paragraph's text, args: <index> <text>",
		bind(&DocumentMenu::ReplaceText, this, _1));
	AddItem("ResizeImage", "Resize image, args: <index> <width> <height>",
		bind(&DocumentMenu::ResizeImage, this, _1));
	AddItem("DeleteItem", "Delete item at specified index, args: <index>",
		bind(&DocumentMenu::DeleteItem, this, _1));
	AddItem("Save", "Save document to file in specified format, args: <path>",
		bind(&DocumentMenu::Save, this, _1));
	AddItem("Undo", "Undo last performed command", bind(&DocumentMenu::Undo, this, _1));
	AddItem("Redo", "Redo last undoned command", bind(&DocumentMenu::Redo, this, _1));
}

bool DocumentMenu::EnsureArgumentsCount(const uint64_t& expected, const uint64_t& count)
{
	if (expected != count)
	{
		m_output << "Expected " << expected << " arguments, " << count << " given" << std::endl;
		return false;
	}
	return true;
}

void DocumentMenu::SetDocumentTitle(std::vector<std::string> const& args)
{
	if (!EnsureArgumentsCount(1u, args.size()))
	{
		return;
	}
	m_document.SetTitle(args.front());
}

void DocumentMenu::InsertParagraph(std::vector<std::string> const& args)
{
	if (!EnsureArgumentsCount(2u, args.size()))
	{
		return;
	}
	m_document.InsertParagraph(args[1], ReadAsDocumentPosition(args.front()));
}

void DocumentMenu::InsertImage(std::vector<std::string> const& args)
{
	if (!EnsureArgumentsCount(4u, args.size()))
	{
		return;
	}

	const auto position = ReadAsDocumentPosition(args.front());
	const auto width = ReadAsUnsigned(args[1]);
	const auto height = ReadAsUnsigned(args[2]);
	const auto& path = args[3];

	m_document.InsertImage(path, width, height, position);
}

void DocumentMenu::List(std::vector<std::string> const& args)
{
	if (!EnsureArgumentsCount(0u, args.size()))
	{
		return;
	}

	m_output << "Title: " << m_document.GetTitle() << "\n";
	for (size_t i = 0; i < m_document.GetItemsCount(); ++i)
	{
		m_output << i << ". " << GetDescription(*m_document.GetItem(i)) << "\n";
	}
}

void DocumentMenu::ReplaceText(std::vector<std::string> const& args)
{
	if (!EnsureArgumentsCount(2u, args.size()))
	{
		return;
	}
	m_document.ReplaceText(args[1], ReadAsIndex(args.front()));
}

void DocumentMenu::ResizeImage(std::vector<std::string> const& args)
{
	if (!EnsureArgumentsCount(3u, args.size()))
	{
		return;
	}
	m_document.ResizeImage(ReadAsUnsigned(args[1]), ReadAsUnsigned(args[2]), ReadAsIndex(args.front()));
}

void DocumentMenu::DeleteItem(std::vector<std::string> const& args)
{
	if (!EnsureArgumentsCount(1u, args.size()))
	{
		return;
	}
	m_document.RemoveItem(ReadAsIndex(args.front()));
}

void DocumentMenu::Save(std::vector<std::string> const& args)
{
	if (!EnsureArgumentsCount(1u, args.size()))
	{
		return;
	}
	m_document.Save(args.front());
}

void DocumentMenu::Undo(std::vector<std::string> const& args)
{
	if (!EnsureArgumentsCount(0u, args.size()))
	{
		return;
	}

	if (m_document.CanUndo())
	{
		m_document.Undo();
	}
	else
	{
		m_output << "Can't undo" << std::endl;
	}
}

void DocumentMenu::Redo(std::vector<std::string> const& args)
{
	if (!EnsureArgumentsCount(0u, args.size()))
	{
		return;
	}

	if (m_document.CanRedo())
	{
		m_document.Redo();
	}
	else
	{
		m_output << "Can't redo" << std::endl;
	}
}
