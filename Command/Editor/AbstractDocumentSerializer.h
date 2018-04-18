#pragma once
#include <string>
#include <iosfwd>
#include <memory>

class AbstractDocumentSerializer
{
public:
	void Serialize(const std::string& path)const;

	virtual void SetTitle(const std::string& title) = 0;
	virtual void InsertImage(const std::string& path, unsigned width, unsigned height) = 0;
	virtual void InsertParagraph(const std::string& text) = 0;

protected:
	virtual void SerializeImpl(std::ostream& output)const = 0;
};

std::unique_ptr<AbstractDocumentSerializer> CreateSerializer(const std::string& path);
