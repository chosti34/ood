#include "stdafx.h"
#include "ResizeImageCommand.h"

ResizeImageCommand::ResizeImageCommand(IImage& image, const ImageSize& newSize)
	: m_image(image)
	, m_newSize(newSize)
	, m_oldSize({ image.GetWidth(), image.GetHeight() })
{
}

void ResizeImageCommand::ExecuteImpl()
{
	m_image.Resize(m_newSize.first, m_newSize.second);
}

void ResizeImageCommand::UnexecuteImpl()
{
	m_image.Resize(m_oldSize.first, m_oldSize.second);
}
