#pragma once
#include <string>
#include <vector>

class IDocumentSerializer
{
public:
	virtual void AddParagraph(const std::string& text) = 0;
	virtual void AddImage(const std::string& path, unsigned width, unsigned height) = 0;
	virtual std::string Serialize(const std::string& title)const = 0;
};

// Сериализует документ в HTML
class HtmlDocumentSerializer : public IDocumentSerializer
{
public:
	HtmlDocumentSerializer();

	void AddParagraph(const std::string& text) override;
	void AddImage(const std::string& path, unsigned width, unsigned height) override;

	std::string Serialize(const std::string& title)const override;

private:
	std::vector<std::string> m_elements;
};

// Сериализует документ в JSON
class JsonDocumentSerializer : public IDocumentSerializer
{
public:
	JsonDocumentSerializer();

	void AddParagraph(const std::string& text) override;
	void AddImage(const std::string& path, unsigned width, unsigned height) override;

	std::string Serialize(const std::string& title)const override;

private:
	std::vector<std::string> m_elements;
};

// Сериализует документ в XML
class XmlDocumentSerializer : public IDocumentSerializer
{
public:
	XmlDocumentSerializer();

	void AddParagraph(const std::string& text) override;
	void AddImage(const std::string& path, unsigned width, unsigned height) override;

	std::string Serialize(const std::string& title)const override;

private:
	std::vector<std::string> m_elements;
};
