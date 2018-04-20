#pragma once
#include "IParagraph.h"
#include "ICommandManager.h"

class Paragraph : public IParagraph
{
public:
	Paragraph(const std::string& text, ICommandManager& manager);

	std::string GetText() const override;
	void SetText(const std::string& text) override;

private:
	std::string m_text;
	ICommandManager& m_manager;
};
