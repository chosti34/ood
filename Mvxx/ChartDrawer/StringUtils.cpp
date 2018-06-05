#include "stdafx.h"
#include "StringUtils.h"

std::string StringUtils::FloatToString(float value, unsigned precision)
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(precision) << value;
	return strm.str();
}

std::wstring StringUtils::FloatToWideString(float value, unsigned precision)
{
	std::wostringstream strm;
	strm << std::fixed << std::setprecision(precision) << value;
	return strm.str();
}
