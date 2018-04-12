#include "stdafx.h"
#include "DocumentSerializer.h"
#include <boost/format.hpp>

namespace
{
const std::unordered_map<std::string, std::string> XML_SPECIAL_CHARS = {
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "\"", "&quot;" },
	{ "'", "&apos;" },
	{ "&", "&amp;" }
};

const std::unordered_map<std::string, std::string> JSON_SPECIAL_CHARS = {
	{ "\b", "\\b" },
	{ "\f", "\\f" },
	{ "\n", "\\n" },
	{ "\r", "\\r" },
	{ "\t", "\\t" },
	{ "\"", "\\\"" },
	{ "\\", "\\\\" }
};

std::string EscapeSpecialCharacters(const std::string& content,
	const std::unordered_map<std::string, std::string>& specialChars)
{
	std::string escaped;
	escaped.reserve(content.length());

	size_t i = 0;
	while (i < content.length())
	{
		bool replaced = false;
		for (const auto& pair : specialChars)
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

// HTML
HtmlDocumentSerializer::HtmlDocumentSerializer()
	: m_elements()
{
}

void HtmlDocumentSerializer::AddParagraph(const std::string& text)
{
	m_elements.push_back("<p>" + EscapeSpecialCharacters(text, XML_SPECIAL_CHARS) + "</p>");
}

void HtmlDocumentSerializer::AddImage(const std::string& path, unsigned width, unsigned height)
{
	using std::to_string;
	
	const std::string img =
		"<img src=\"" + EscapeSpecialCharacters(path, XML_SPECIAL_CHARS) + "\" width=\"" + to_string(width) +
		"\" height=\"" + to_string(height) + "\" />";
	
	m_elements.push_back(img);
}

std::string HtmlDocumentSerializer::Serialize(const std::string& title)const
{
	std::ostringstream content;
	content
		<< "<!DOCTYPE html>\n"
		<< "<html>\n"
		<< "  <head>\n"
		<< "    <meta charset=\"utf-8\" />\n"
		<< "    <title>" + EscapeSpecialCharacters(title, XML_SPECIAL_CHARS) + "</title>\n"
		<< "  </head>\n"
		<< "  <body>\n";
	
	for (const auto& element : m_elements)
	{
		content << std::string(4u, ' ') << element << "\n";
	}
	
	content
		<< "  </body>\n"
		<< "</html>\n";
	return content.str();
}

// JSON
JsonDocumentSerializer::JsonDocumentSerializer()
	: m_elements()
{
}

void JsonDocumentSerializer::AddParagraph(const std::string& text)
{
	auto fmt = boost::format(R"(  "paragraph: {
    "text": "%1%"
  })");

	m_elements.push_back((fmt % EscapeSpecialCharacters(text, JSON_SPECIAL_CHARS)).str());
}

void JsonDocumentSerializer::AddImage(const std::string& path, unsigned width, unsigned height)
{
	auto fmt = boost::format(R"(  "image": {
    "path": "%1%",
    "width": "%2%",
    "height": %3%
  })");

	m_elements.push_back((fmt % EscapeSpecialCharacters(path, JSON_SPECIAL_CHARS) % width % height).str());
}

std::string JsonDocumentSerializer::Serialize(const std::string & title)const
{
	std::ostringstream content;
	content
		<< "{\n"
		<< std::string(2u, ' ')
		<< "\"title\": " << EscapeSpecialCharacters(title, JSON_SPECIAL_CHARS);

	for (const auto& element : m_elements)
	{
		content << ",\n" << element;
	}

	content << "\n}\n";
	return content.str();
}

// XML
XmlDocumentSerializer::XmlDocumentSerializer()
	: m_elements()
{
}

void XmlDocumentSerializer::AddParagraph(const std::string& text)
{
	auto fmt = boost::format(R"(  <Paragraph>
    <Text>%1%</Text>
  </Paragraph>)");

	m_elements.push_back((fmt % EscapeSpecialCharacters(text, XML_SPECIAL_CHARS)).str());
}

void XmlDocumentSerializer::AddImage(const std::string& path, unsigned width, unsigned height)
{
	auto fmt = boost::format(R"(  <Image width="%1%" height="%2%">
    <Path>%3%</Path>
  </Image>)");

	m_elements.push_back((fmt % width % height % EscapeSpecialCharacters(path, XML_SPECIAL_CHARS)).str());
}

std::string XmlDocumentSerializer::Serialize(const std::string& title)const
{
	std::ostringstream content;
	content << "<Document title=\"" << EscapeSpecialCharacters(title, XML_SPECIAL_CHARS) << "\">\n";

	for (const auto& element : m_elements)
	{
		content << element << "\n";
	}

	content << "</Document>\n";
	return content.str();
}
