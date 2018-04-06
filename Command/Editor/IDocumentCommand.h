#pragma once
#include "IDocumentControl.h"

class IDocumentCommand
{
public:
	virtual ~IDocumentCommand() = default;
	virtual void Execute(IDocumentControl& control) = 0;
	virtual void Unexecute(IDocumentControl& control) = 0;
};

using IDocumentCommandPtr = std::unique_ptr<IDocumentCommand>;
