#pragma once
#include <memory>

class ICommand
{
public:
	virtual ~ICommand() = default;
	virtual bool Execute() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};

using ICommandPtr = std::unique_ptr<ICommand>;
