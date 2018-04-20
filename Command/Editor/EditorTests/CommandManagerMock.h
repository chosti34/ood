#pragma once
#include "../ICommandManager.h"
#include <vector>
#include <ostream>

class CommandManagerMock : public ICommandManager
{
public:
	CommandManagerMock(std::ostream& output)
		: m_output(output)
	{
	}

	void ApplyCommand(std::unique_ptr<ICommand>&& command) override
	{
		command->Execute();
		m_output << "Command executed";
		m_undoStack.push_back(std::move(command));
		m_redoStack.clear();
	}

	bool CanUndo() const override
	{
		return false;
	}

	bool CanRedo() const override
	{
		return false;
	}

	void Undo() override
	{
		if (!m_undoStack.empty())
		{
			m_undoStack.back()->Unexecute();
			m_output << "Command unexecuted";
			m_redoStack.push_back(std::move(m_undoStack.back()));
			m_undoStack.pop_back();
		}
	}

	void Redo() override
	{
		if (!m_redoStack.empty())
		{
			m_redoStack.back()->Execute();
			m_output << "Command reexecuted";
			m_undoStack.push_back(std::move(m_redoStack.back()));
			m_redoStack.pop_back();
		}
	}

private:
	std::ostream& m_output;
	std::vector<std::unique_ptr<ICommand>> m_undoStack;
	std::vector<std::unique_ptr<ICommand>> m_redoStack;
};
