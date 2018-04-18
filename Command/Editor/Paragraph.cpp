#include "stdafx.h"
#include "Paragraph.h"
#include "ChangeStringCommand.h"

Paragraph::Paragraph(const std::string& text, ICommandManager& manager)
	: m_text(text)
	, m_manager(manager)
{
}

std::string Paragraph::GetText() const
{
	return m_text;
}

void Paragraph::SetText(const std::string& text)
{
	m_manager.ApplyCommand(std::make_unique<ChangeStringCommand>(m_text, text));
}
