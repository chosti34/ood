#include "stdafx.h"
#include "Image.h"

Image::Image(const std::string& path, unsigned width, unsigned height)
	: m_path(path)
	, m_width(width)
	, m_height(height)
{
}

std::string Image::GetPath() const
{
	return m_path;
}

int Image::GetWidth() const
{
	return m_width;
}

int Image::GetHeight() const
{
	return m_height;
}

void Image::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}
