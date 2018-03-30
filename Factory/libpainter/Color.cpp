#include "stdafx.h"
#include "Color.h"
#include <iomanip>

std::string ToString(const Color& color)
{
	std::ostringstream strm;
	strm << std::hex << std::setfill('0');
	strm << std::setw(2u) << static_cast<int>(color.r);
	strm << std::setw(2u) << static_cast<int>(color.g);
	strm << std::setw(2u) << static_cast<int>(color.b);
	return strm.str();
}
