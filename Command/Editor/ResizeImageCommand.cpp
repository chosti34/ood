#include "stdafx.h"
#include "ResizeImageCommand.h"

ResizeImageCommand::ResizeImageCommand(const Size& newSize, const Size& oldSize, size_t index)
	: m_newSize(newSize)
	, m_oldSize(oldSize)
{
}

void ResizeImageCommand::Execute(IDocumentCommandControl& control)
{
	control.DoResizeImage(m_newSize.first, m_newSize.second, m_index);
}

void ResizeImageCommand::Unexecute(IDocumentCommandControl& control)
{
	control.DoResizeImage(m_oldSize.first, m_oldSize.second, m_index);
}
