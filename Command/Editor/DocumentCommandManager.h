#pragma once
#include "IDocumentCommand.h"
#include <vector>

class DocumentCommandManager
{
public:
	DocumentCommandManager(unsigned commandsDepth);

	void RegisterCommand(IDocumentCommandPtr&& command);

	bool CanUndo()const;
	bool CanRedo()const;

	void Undo(IDocument& document);
	void Redo(IDocument& document);

private:
	unsigned m_commandsDepth;
	std::vector<std::unique_ptr<IDocumentCommand>> m_undoStack;
	std::vector<std::unique_ptr<IDocumentCommand>> m_redoStack;
};
