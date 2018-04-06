#pragma once
#include "IDocumentCommand.h"
#include <boost/optional.hpp>
#include <string>

class InsertParagraphCommand : public IDocumentCommand
{
public:
	InsertParagraphCommand(const std::string& text, boost::optional<size_t> index = boost::none);

	void Execute(IDocumentControl& control) override;
	void Unexecute(IDocumentControl& control) override;

private:
	std::string m_text;
	boost::optional<size_t> m_index;
};
