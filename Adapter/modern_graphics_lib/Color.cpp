#include "stdafx.h"
#include "Color.h"

modern_graphics_lib::Color::Color(float r, float g, float b, float a)
	: r(r)
	, g(g)
	, b(b)
	, a(a)
{
}

modern_graphics_lib::Color modern_graphics_lib::ToRGBA(uint32_t rgb)
{
	modern_graphics_lib::Color color(0, 0, 0, 1);
	color.r = ((rgb >> 16) & 0xff) / 255.f;
	color.g = ((rgb >> 8) & 0xff) / 255.f;
	color.b = (rgb & 0xff) / 255.f;
	return color;
}
