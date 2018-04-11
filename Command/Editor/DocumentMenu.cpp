#include "stdafx.h"
#include "DocumentMenu.h"
#include "DocumentSerializer.h"
#include "ImageFileStorage.h"

namespace
{
void WriteToFile(const std::string& filePath, const std::string& content)
{
	std::ofstream file(filePath);
	if (!file)
	{
		throw std::runtime_error("failed to open " + filePath + " for writing");
	}
	file << content;
}

// В случае "end" -> boost::none
// иначе попытка считать как size_t
boost::optional<size_t> ReinterpretAsDocumentPosition(const std::string& str)
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

DocumentMenu::DocumentMenu(IDocument& document, IImageFileStorage& storage, std::ostream& output)
	: m_document(document)
	, m_storage(storage)
	, Menu(output)
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
	AddItem("Save", "Save document to file in HTML format, args: <path>",
		bind(&DocumentMenu::Save, this, _1));
	AddItem("Undo", "Undo last performed command", bind(&DocumentMenu::Undo, this, _1));
	AddItem("Redo", "Redo last undoned command", bind(&DocumentMenu::Redo, this, _1));
}

bool DocumentMenu::EnsureArgumentsCount(uint64_t expected, uint64_t count)
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
	m_document.InsertParagraph(args[1], ReinterpretAsDocumentPosition(args.front()));
}

void DocumentMenu::InsertImage(std::vector<std::string> const& args)
{
	if (!EnsureArgumentsCount(4u, args.size()))
	{
		return;
	}

	const auto position = ReinterpretAsDocumentPosition(args.front());
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

	m_output << "Document's title: '" << m_document.GetTitle() << "'" << std::endl;
	for (size_t index = 0; index < m_document.GetItemsCount(); ++index)
	{
		const auto& item = m_document.GetItem(index);
		m_output << index << ". " << GetDocumentItemDescription(*item) << std::endl;
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

	const auto index = ReadAsIndex(args.front());
	const auto width = ReadAsUnsigned(args[1]);
	const auto height = ReadAsUnsigned(args[2]);

	m_document.ResizeImage(width, height, index);
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

	DocumentSerializer serializer;
	serializer.SetTitle(m_document.GetTitle());

	for (size_t i = 0; i < m_document.GetItemsCount(); ++i)
	{
		const auto& paragraph = m_document.GetItem(i)->GetParagraph();
		const auto& image = m_document.GetItem(i)->GetImage();
		assert(paragraph || image);

		if (paragraph)
		{
			assert(!image);
			serializer.AddParagraph(paragraph->GetText());
		}
		if (image)
		{
			assert(!paragraph);
			serializer.AddImage(image->GetPath(), image->GetWidth(), image->GetHeight());
		}
	}

	WriteToFile(args.front(), serializer.Serialize());
	m_storage.CopyTo(args.front());
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
