#pragma once
#include <string>
#include <unordered_map>

std::string EscapeXML(const std::string& content);
std::string EscapeJSON(const std::string& content);

std::string ReplaceAll(
	const std::string& content,
	const std::unordered_map<std::string, std::string>& replacements);
