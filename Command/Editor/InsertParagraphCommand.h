#pragma once
#include "IDocumentCommand.h"
#include <string>
#include <boost/optional.hpp>

class InsertParagraphCommand : public IDocumentCommand
{
public:
	InsertParagraphCommand(
		const std::string& text,
		boost::optional<size_t> pos = boost::none);

	bool Execute(IDocument& document) override;
	void Undo(IDocument& document) override;
	void Redo(IDocument& document) override;

private:
	std::string m_text;
	boost::optional<size_t> m_pos;
	boost::optional<size_t> m_insertedAtPos;
};
