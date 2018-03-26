#include "stdafx.h"
#include "Color.h"

namespace
{
constexpr uint8_t BUFFER_SIZE = 3u;
}

extern Color GREEN_COLOR = { 0, 255, 0 };
extern Color RED_COLOR = { 255, 0, 0 };
extern Color BLUE_COLOR = { 0, 0, 255 };
extern Color YELLOW_COLOR = { 255, 255, 0 };
extern Color PINK_COLOR = { 255, 45, 180 };
extern Color BLACK_COLOR = { 0, 0, 0 };

std::string Color::ToString()const
{
	std::string result;

	char red[BUFFER_SIZE];
	sprintf_s(red, "%.2X", r);
	result.append(red);

	char green[BUFFER_SIZE];
	sprintf_s(green, "%.2X", g);
	result.append(green);

	char blue[BUFFER_SIZE];
	sprintf_s(blue, "%.2X", b);
	result.append(blue);

	return result;
}
