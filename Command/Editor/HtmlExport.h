#pragma once
#include <string>
class IDocument;

void ExportAsHtmlDocument(const std::string& path, const IDocument& document);
