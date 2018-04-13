#pragma once
#include "AbstractCommand.h"
#include "IDocumentCommandControl.h"
#include <string>

class SetTitleCommand : public AbstractCommand
{
public:
	SetTitleCommand(
		IDocumentCommandControl& control,
		const std::string& newTitle,
		const std::string& oldTitle);

private:
	void ExecuteImpl() override;
	void UnexecuteImpl() override;

private:
	IDocumentCommandControl& m_control;
	std::string m_newTitle;
	std::string m_oldTitle;
};
