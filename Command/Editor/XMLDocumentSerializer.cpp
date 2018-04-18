#include "stdafx.h"
#include "XMLDocumentSerializer.h"
#include "EscapeString.h"
#include <boost/format.hpp>

void XMLDocumentSerializer::SetTitle(const std::string& title)
{
	m_title = EscapeXML(title);
}

void XMLDocumentSerializer::InsertImage(const std::string& path, unsigned width, unsigned height)
{
	auto format = boost::format(R"(  <Image width="%1%" height="%2%">
    <Path>%3%</Path>
  </Image>
)");

	m_items.push_back((format % width % height % EscapeXML(path)).str());
}

void XMLDocumentSerializer::InsertParagraph(const std::string& text)
{
	auto format = boost::format(R"(  <Paragraph>
    <Text>%1%</Text>
  </Paragraph>
)");

	m_items.push_back((format % EscapeXML(text)).str());
}

void XMLDocumentSerializer::SerializeImpl(std::ostream& output)const
{
	output << "<Document title=\"" << m_title << "\">\n";
	for (const auto& item : m_items)
	{
		output << item;
	}
	output << "</Document>\n";
}
