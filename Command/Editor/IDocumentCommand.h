#pragma once
#include "IDocumentCommandControl.h"

class IDocumentCommand
{
public:
	virtual ~IDocumentCommand() = default;
	virtual void Execute(IDocumentCommandControl& control) = 0;
	virtual void Unexecute(IDocumentCommandControl& control) = 0;
};

using IDocumentCommandPtr = std::unique_ptr<IDocumentCommand>;
