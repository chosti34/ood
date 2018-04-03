#pragma once
#include "ICommandFactory.h"

class CommandFactory : public ICommandFactory
{
public:
	ICommandPtr CreateCommand(const std::string & description)override;
};
