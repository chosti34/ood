#pragma once
#include "ICommandManager.h"
#include "IDocument.h"
#include <deque>

class DocumentCommandManager : public ICommandManager
{
public:
	DocumentCommandManager(unsigned historyDepth);

	void RegisterCommand(std::unique_ptr<ICommand>&& command) override;

	bool CanUndo()const override;
	bool CanRedo()const override;

	void Undo() override;
	void Redo() override;

private:
	unsigned m_historyDepth;
	std::deque<std::unique_ptr<ICommand>> m_undoStack;
	std::deque<std::unique_ptr<ICommand>> m_redoStack;
};
