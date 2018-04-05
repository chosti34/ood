#pragma once
#include "IDocument.h"
#include "Menu.h"

class DocumentInputControl
{
public:
	DocumentInputControl(IDocument& document, Menu& menu);

private:
	void DoMenuExitCommand(std::istream& strm);
	void DoShowInstructionsCommand(std::istream& strm);
	void DoSetTitleCommand(std::istream& strm);
	void DoInsertParagraphCommand(std::istream& strm);
	void DoListCommand(std::istream& strm);
	void DoReplaceTextCommand(std::istream& strm);
	void DoDeleteItemCommand(std::istream& strm);
	void DoSaveCommand(std::istream& strm);
	void DoUndoCommand(std::istream& strm);
	void DoRedoCommand(std::istream& strm);

private:
	IDocument & m_document;
	Menu& m_menu;
};
