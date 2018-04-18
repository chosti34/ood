#include "stdafx.h"
#include "Image.h"
#include "ResizeImageCommand.h"

namespace
{
bool ImageSizeAllowed(unsigned size)
{
	return size >= 1u && size <= 10000u;
}

void EnsureImageSizeAllowed(unsigned width, unsigned height)
{
	if (!ImageSizeAllowed(width))
	{
		throw std::invalid_argument("image's width must be in range [1 .. 10000]");
	}
	if (!ImageSizeAllowed(height))
	{
		throw std::invalid_argument("image's height must be in range [1 .. 10000]");
	}
}
}

Image::Image(const std::string& path, unsigned width, unsigned height, ICommandManager& manager)
	: m_path(path)
	, m_manager(manager)
{
	EnsureImageSizeAllowed(width, height);
	m_width = width;
	m_height = height;
}

std::string Image::GetPath()const
{
	return m_path;
}

unsigned Image::GetWidth()const
{
	return m_width;
}

unsigned Image::GetHeight()const
{
	return m_height;
}

void Image::Resize(unsigned width, unsigned height)
{
	EnsureImageSizeAllowed(width, height);
	m_manager.ApplyCommand(std::make_unique<ResizeImageCommand>(m_width, m_height, width, height));
}
