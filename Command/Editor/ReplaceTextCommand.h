#pragma once
#include "AbstractCommand.h"
#include "IParagraph.h"

class ReplaceTextCommand final : public AbstractCommand
{
public:
	ReplaceTextCommand(IParagraph& paragraph, const std::string& newText);

private:
	void ExecuteImpl() override;
	void UnexecuteImpl() override;

private:
	IParagraph& m_paragraph; // Параграф не должен быть удалён, пока эта команда жива
	std::string m_newText;
	std::string m_oldText;
};
