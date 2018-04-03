#pragma once
#include "ICommand.h"
#include <string>

class ICommandFactory
{
public:
	virtual ICommandPtr CreateCommand(const std::string& description) = 0;
};
