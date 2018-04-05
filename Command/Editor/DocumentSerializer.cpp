#include "stdafx.h"
#include "DocumentSerializer.h"
#include "IDocument.h"

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

void DocumentSerializer::SerializeAsHTML(const std::string& path, const IDocument& document)
{
	std::ofstream output(path);
	if (!output)
	{
		throw std::runtime_error("failed to open " + path + " for serializing");
	}

	std::ostringstream strm;
	strm << "<!DOCTYPE html>\n<html>\n  <head>\n    <meta charset=\"utf-8\">\n    <title>"
		<< EscapeSpecialCharacters(document.GetTitle()) << "</title>\n"
		<< "  <body>\n";

	for (size_t i = 0; i < document.GetItemsCount(); ++i)
	{
		auto item = document.GetItem(i);
		if (item->GetParagraph())
		{
			strm << "    <p>";
			assert(!item->GetImage());
			strm << EscapeSpecialCharacters(item->GetParagraph()->GetText());
			strm << "</p>\n";
		}
	}

	strm << "  </body>\n</html>\n";
	output << strm.str();
}
