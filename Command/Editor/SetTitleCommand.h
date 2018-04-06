#pragma once
#include "IDocumentCommand.h"
#include "IDocumentControl.h"
#include <string>

class SetTitleCommand : public IDocumentCommand
{
public:
	SetTitleCommand(const std::string& newTitle, const std::string& oldTitle);

	void Execute(IDocumentControl& control) override;
	void Unexecute(IDocumentControl& control) override;

private:
	std::string m_newTitle;
	std::string m_oldTitle;
};
