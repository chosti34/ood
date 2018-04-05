#pragma once
#include "IDocumentCommand.h"
#include <deque>

class DocumentCommandManager
{
public:
	DocumentCommandManager(unsigned historyDepth);

	void RegisterCommand(IDocumentCommandPtr&& command);

	bool CanUndo()const;
	bool CanRedo()const;

	void Undo(IDocument& document);
	void Redo(IDocument& document);

private:
	unsigned m_historyDepth;
	std::deque<std::unique_ptr<IDocumentCommand>> m_undoStack;
	std::deque<std::unique_ptr<IDocumentCommand>> m_redoStack;
};
