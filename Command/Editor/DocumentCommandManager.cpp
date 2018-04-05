#include "stdafx.h"
#include "DocumentCommandManager.h"

DocumentCommandManager::DocumentCommandManager(unsigned commandsDepth)
	: m_undoStack()
	, m_redoStack()
	, m_commandsDepth(commandsDepth)
{
}

void DocumentCommandManager::RegisterCommand(IDocumentCommandPtr&& command)
{
	m_undoStack.push_back(std::move(command));
}

bool DocumentCommandManager::CanUndo()const
{
	return !m_undoStack.empty();
}

bool DocumentCommandManager::CanRedo()const
{
	return !m_redoStack.empty();
}

void DocumentCommandManager::Undo(IDocument& document)
{
	assert(CanUndo());
	m_undoStack.back()->Undo(document);
	m_redoStack.push_back(std::move(m_undoStack.back()));
	m_undoStack.pop_back();
}

void DocumentCommandManager::Redo(IDocument& document)
{
	assert(CanRedo());
	m_redoStack.back()->Redo(document);
	m_undoStack.push_back(std::move(m_redoStack.back()));
	m_redoStack.pop_back();
}
