#pragma once
#include <string>
class IDocument;

class DocumentSerializer
{
public:
	void SerializeAsHTML(const std::string& path, const IDocument& document);
};
