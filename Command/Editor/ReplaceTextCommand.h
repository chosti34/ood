#pragma once
#include "IDocumentCommand.h"
#include <string>

class ReplaceTextCommand : public IDocumentCommand
{
public:
	ReplaceTextCommand(size_t pos, const std::string& text) {}

	bool Execute(IDocument & document) override;
	void Undo(IDocument & document) override;
	void Redo(IDocument & document) override;

private:
	size_t m_pos;
	std::string m_text;
};
