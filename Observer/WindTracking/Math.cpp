#include "stdafx.h"
#include "Math.h"
#include <boost/math/constants/constants.hpp>

namespace
{
constexpr double PI = boost::math::constants::pi<double>();
}

double DegreesToRadians(double degrees)
{
	return degrees * PI / 180.0;
}

double RadiansToDegrees(double radians)
{
	return radians * 180.0 / PI;
}
