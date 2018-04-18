#include "stdafx.h"
#include "HTMLDocumentSerializer.h"
#include "EscapeString.h"
#include <boost/format.hpp>

void HTMLDocumentSerializer::SetTitle(const std::string& title)
{
	m_title = EscapeXML(title);
}

void HTMLDocumentSerializer::InsertImage(const std::string& path, unsigned width, unsigned height)
{
	auto format = boost::format(R"(<img src="%1%" width="%2%" height="%3%" />)");
	m_items.push_back((format % EscapeXML(path) % width % height).str());
}

void HTMLDocumentSerializer::InsertParagraph(const std::string& text)
{
	m_items.push_back("<p>" + EscapeXML(text) + "</p>");
}

void HTMLDocumentSerializer::SerializeImpl(std::ostream& output)const
{
	output << R"(<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8" />
    <title>)" << m_title << R"(</title>
  </head>
  <body>
)";

	for (const auto& item : m_items)
	{
		output << std::string(4u, ' ') <<  item << "\n";
	}

	output << R"(  </body>
</html>
)";
}
