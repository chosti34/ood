#pragma once
#include "IDocumentCommand.h"
#include "IDocumentCommandControl.h"
#include <string>

class ReplaceTextCommand : public IDocumentCommand
{
public:
	ReplaceTextCommand(const std::string& newText, const std::string& oldText, size_t index);

	void Execute(IDocumentCommandControl& control) override;
	void Unexecute(IDocumentCommandControl& control) override;

private:
	size_t m_index;
	std::string m_newText;
	std::string m_oldText;
};
