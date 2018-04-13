#pragma once
#include "ICommand.h"
#include <memory>

class ICommandManager
{
public:
	virtual ~ICommandManager() = default;

	virtual void RegisterCommand(std::unique_ptr<ICommand>&& command) = 0;

	virtual bool CanUndo()const = 0;
	virtual bool CanRedo()const = 0;

	virtual void Undo() = 0;
	virtual void Redo() = 0;
};
