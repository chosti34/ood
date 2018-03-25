#pragma once
#include <cstdint>
#include <string>

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	std::string ToString()const
	{
		std::string result;

		char r[3];
		sprintf_s(r, "%.2X", this->r);
		result.append(r);

		char g[3];
		sprintf_s(g, "%.2X", this->b);
		result.append(g);

		char b[3];
		sprintf_s(b, "%.2X", this->g);
		result.append(b);

		return result;
	}
};
