#include "stdafx.h"
#include "DocumentSerializer.h"

namespace
{
const std::unordered_map<std::string, std::string> HTML_SPECIAL_CHARS = {
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "\"", "&quot;" },
	{ "'", "&apos;" },
	{ "&", "&amp;" }
};

std::string EscapeSpecialCharacters(const std::string& content)
{
	std::string escaped;
	escaped.reserve(content.length());

	size_t i = 0;
	while (i < content.length())
	{
		bool replaced = false;
		for (const auto& pair : HTML_SPECIAL_CHARS)
		{
			const auto& specialChar = pair.first;
			const auto& replacement = pair.second;

			if (content.compare(i, specialChar.length(), specialChar) == 0)
			{
				escaped.append(replacement);
				i += specialChar.length();
				replaced = true;
				break;
			}
		}
		if (!replaced)
		{
			escaped += content[i++];
		}
	}

	return escaped;
}
}

DocumentSerializer::DocumentSerializer()
	: m_body()
	, m_title()
{
}

void DocumentSerializer::SetTitle(const std::string& title)
{
	m_title = EscapeSpecialCharacters(title);
}

void DocumentSerializer::AddParagraph(const std::string& text)
{
	m_body.push_back("<p>" + EscapeSpecialCharacters(text) + "</p>");
}

void DocumentSerializer::AddImage(const std::string& path, unsigned width, unsigned height)
{
	using std::to_string;

	const std::string img =
		"<img src=\"" + EscapeSpecialCharacters(path) + "\" width=\"" + to_string(width) +
		"\" height=\"" + to_string(height) + "\" />";

	m_body.push_back(img);
}

std::string DocumentSerializer::Serialize() const
{
	std::ostringstream content;

	content
		<< "<!DOCTYPE html>\n"
		<< "<html>\n"
		<< "  <head>\n"
		<< "    <meta charset=\"utf-8\" />\n"
		<< "    <title>" + m_title + "</title>\n"
		<< "  </head>\n"
		<< "  <body>\n";

	for (const auto& element : m_body)
	{
		content << std::string(4u, ' ') << element << "\n";
	}

	content
		<< "  </body>\n"
		<< "</html>\n";

	return content.str();
}
