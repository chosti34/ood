#pragma once
#include "IDocumentCommand.h"
#include "IDocumentCommandControl.h"
#include <string>

class SetTitleCommand : public IDocumentCommand
{
public:
	SetTitleCommand(const std::string& newTitle, const std::string& oldTitle);

	void Execute(IDocumentCommandControl& control) override;
	void Unexecute(IDocumentCommandControl& control) override;

private:
	std::string m_newTitle;
	std::string m_oldTitle;
};
