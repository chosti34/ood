#pragma once
#include "IDocumentCommand.h"

#include <string>
#include <boost/optional.hpp>

class SetTitleCommand : public IDocumentCommand
{
public:
	SetTitleCommand(const std::string& title);

	bool Execute(IDocument& document) override;
	void Undo(IDocument& document) override;
	void Redo(IDocument& document) override;

private:
	std::string m_newTitle;
	boost::optional<std::string> m_oldTitle;
};
