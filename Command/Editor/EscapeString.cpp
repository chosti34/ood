#include "stdafx.h"
#include "EscapeString.h"

namespace
{
const std::unordered_map<std::string, std::string> XML_ESCAPE_MAP = {
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "\"", "&quot;" },
	{ "'", "&apos;" },
	{ "&", "&amp;" }
};

const std::unordered_map<std::string, std::string> JSON_ESCAPE_MAP = {
	{ "\b", "\\b" },
	{ "\f", "\\f" },
	{ "\n", "\\n" },
	{ "\r", "\\r" },
	{ "\t", "\\t" },
	{ "\"", "\\\"" },
	{ "\\", "\\\\" }
};
}

std::string EscapeXML(const std::string& content)
{
	return ReplaceAll(content, XML_ESCAPE_MAP);
}

std::string EscapeJSON(const std::string& content)
{
	return ReplaceAll(content, JSON_ESCAPE_MAP);
}

std::string ReplaceAll(
	const std::string& content,
	const std::unordered_map<std::string, std::string>& replacements)
{
	std::string escaped;
	escaped.reserve(content.length());

	size_t i = 0;
	while (i < content.length())
	{
		bool replaced = false;
		for (const auto& pair : replacements)
		{
			const auto& search = pair.first;
			const auto& replacement = pair.second;
			if (content.compare(i, search.length(), search) == 0)
			{
				escaped.append(replacement);
				i += search.length();
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
