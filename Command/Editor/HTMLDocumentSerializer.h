#pragma once
#include "AbstractDocumentSerializer.h"

class HTMLDocumentSerializer : public AbstractDocumentSerializer
{
public:
	void SetTitle(const std::string& title) override;
	void InsertImage(const std::string& path, unsigned width, unsigned height) override;
	void InsertParagraph(const std::string& text) override;

private:
	void SerializeImpl(std::ostream& output)const override;

private:
	std::vector<std::string> m_items;
	std::string m_title;
};
