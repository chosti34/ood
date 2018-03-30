#pragma once
#include <cstdint>
#include <string>

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

std::string ToString(const Color& color);
