#include "stdafx.h"
#include "ResizeImageCommand.h"

ResizeImageCommand::ResizeImageCommand(unsigned& width, unsigned& height, unsigned newWidth, unsigned newHeight)
	: m_width(width)
	, m_height(height)
	, m_newWidth(newWidth)
	, m_newHeight(newHeight)
{
}

void ResizeImageCommand::ExecuteImpl()
{
	std::swap(m_width, m_newWidth);
	std::swap(m_height, m_newHeight);
}

void ResizeImageCommand::UnexecuteImpl()
{
	std::swap(m_width, m_newWidth);
	std::swap(m_height, m_newHeight);
}
