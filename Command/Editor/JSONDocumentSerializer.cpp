#include "stdafx.h"
#include "JSONDocumentSerializer.h"
#include "EscapeString.h"
#include <boost/format.hpp>

void JSONDocumentSerializer::SetTitle(const std::string& title)
{
	m_title = EscapeJSON(title);
}

void JSONDocumentSerializer::InsertImage(const std::string& path, unsigned width, unsigned height)
{
	auto format = boost::format(R"(  "image": {
    "path": "%1%",
    "width": "%2%",
    "height": "%3%"
  })");

	m_items.push_back((format % EscapeJSON(path) % width % height).str());
}

void JSONDocumentSerializer::InsertParagraph(const std::string& text)
{
	auto format = boost::format(R"(  "paragraph": {
    "text": "%1%"
  })");

	m_items.push_back((format % EscapeJSON(text)).str());
}

void JSONDocumentSerializer::SerializeImpl(std::ostream& output) const
{
	output << "{\n  \"title\": \"" << m_title << "\"";
	for (const auto& item : m_items)
	{
		output << ",\n" << item;
	}
	output << "\n}\n";
}
