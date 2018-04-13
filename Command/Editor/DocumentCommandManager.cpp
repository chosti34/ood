#include "stdafx.h"
#include "DocumentCommandManager.h"

DocumentCommandManager::DocumentCommandManager(unsigned historyDepth)
	: m_undoStack()
	, m_redoStack()
	, m_historyDepth(historyDepth)
{
}

void DocumentCommandManager::RegisterCommand(std::unique_ptr<ICommand>&& command)
{
	if (m_undoStack.size() == m_historyDepth)
	{
		m_undoStack.pop_front();
	}
	m_undoStack.push_back(std::move(command));
	m_redoStack.clear();
}

bool DocumentCommandManager::CanUndo()const
{
	return !m_undoStack.empty();
}

bool DocumentCommandManager::CanRedo()const
{
	return !m_redoStack.empty();
}

void DocumentCommandManager::Undo()
{
	if (!CanUndo())
	{
		throw std::logic_error("can't undo");
	}
	auto command = std::move(m_undoStack.back());
	m_undoStack.pop_back();
	command->Unexecute();
	m_redoStack.push_back(std::move(command));
}

void DocumentCommandManager::Redo()
{
	if (!CanRedo())
	{
		throw std::logic_error("can't redo");
	}
	auto command = std::move(m_redoStack.back());
	m_redoStack.pop_back();
	command->Execute();
	m_undoStack.push_back(std::move(command));
}
