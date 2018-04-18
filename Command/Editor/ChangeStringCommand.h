#pragma once
#include "AbstractCommand.h"
#include <string>

class ChangeStringCommand : public AbstractCommand
{
public:
	ChangeStringCommand(std::string& target, const std::string& newValue);

private:
	void ExecuteImpl() override;
	void UnexecuteImpl() override;

private:
	std::string& m_target;
	std::string m_newValue;
};
