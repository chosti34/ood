#pragma once
#include <cstdint>
#include <string>

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

bool operator ==(const Color& lhs, const Color& rhs);
std::string ToString(const Color& color);
