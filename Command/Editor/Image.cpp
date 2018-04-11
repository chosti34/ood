#include "stdafx.h"
#include "Image.h"

namespace
{
constexpr unsigned MIN_DIMENSION_SIZE = 1u;
constexpr unsigned MAX_DIMENSION_SIZE = 10000u;
}

Image::Image(const std::string& path, unsigned width, unsigned height)
	: m_path(path)
{
	SetSize(width, height);
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
	SetSize(width, height);
}

void Image::SetSize(int width, int height)
{
	if (width < MIN_DIMENSION_SIZE || width > MAX_DIMENSION_SIZE)
	{
		throw std::invalid_argument("image's width must be in range [1 .. 10000]");
	}
	if (height < MIN_DIMENSION_SIZE || height > MAX_DIMENSION_SIZE)
	{
		throw std::invalid_argument("image's height must be in range [1 .. 10000]");
	}
	m_width = width;
	m_height = height;
}
