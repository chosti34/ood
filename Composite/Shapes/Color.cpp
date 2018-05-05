#include "stdafx.h"
#include "Color.h"

RGBAColor GetColorComponents(uint32_t color)
{
	uint8_t r = (color >> 24) & 0xff;
	uint8_t g = (color >> 16) & 0xff;
	uint8_t b = (color >> 8) & 0xff;
	uint8_t a = color & 0xff;
	return RGBAColor{ r, g, b, a };
}

uint32_t MapRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a /* = 0xff */)
{
	uint32_t color = 0;
	color |= uint32_t(r) << 24;
	color |= uint32_t(g) << 16;
	color |= uint32_t(b) << 8;
	color |= uint32_t(a);
	return color;
}
