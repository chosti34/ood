#pragma once
#include <cstdint>
#include <string>

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	std::string ToString()const;
};

extern Color GREEN_COLOR;
extern Color RED_COLOR;
extern Color BLUE_COLOR;
extern Color YELLOW_COLOR;
extern Color PINK_COLOR;
extern Color BLACK_COLOR;
