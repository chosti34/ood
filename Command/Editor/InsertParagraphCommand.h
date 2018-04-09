#pragma once
#include "IDocumentCommand.h"
#include <boost/optional.hpp>
#include <string>

class InsertParagraphCommand : public IDocumentCommand
{
public:
	InsertParagraphCommand(const std::string& text, boost::optional<size_t> position);

	void Execute(IDocumentCommandControl& control) override;
	void Unexecute(IDocumentCommandControl& control) override;

private:
	std::string m_text;
	boost::optional<size_t> m_position;
};
