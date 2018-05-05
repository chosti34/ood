#pragma once
#include <cstdint>

struct RGBAColor
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

RGBAColor GetColorComponents(uint32_t color);
uint32_t MapRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xff);
