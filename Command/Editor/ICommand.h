#pragma once
#include <memory>
class IDocument;

class ICommand
{
public:
	virtual ~ICommand() = default;
	virtual bool Execute(IDocument& document) = 0;
	virtual void Undo(IDocument& document) = 0;
	virtual void Redo(IDocument& document) = 0;
};

using ICommandPtr = std::unique_ptr<ICommand>;
