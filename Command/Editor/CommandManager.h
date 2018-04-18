#pragma once
#include "ICommandManager.h"
#include "IDocument.h"
#include <deque>

class CommandManager : public ICommandManager
{
public:
	CommandManager(unsigned historyDepth);

	void ApplyCommand(std::unique_ptr<ICommand>&& command) override;

	bool CanUndo()const override;
	bool CanRedo()const override;

	void Undo() override;
	void Redo() override;

private:
	unsigned m_historyDepth;
	std::deque<std::unique_ptr<ICommand>> m_undoStack;
	std::deque<std::unique_ptr<ICommand>> m_redoStack;
};
