#pragma once
#include <iosfwd>

struct Point2D
{
	float x;
	float y;
};

bool operator ==(const Point2D& lhs, const Point2D& rhs);
std::istream& operator >>(std::istream& strm, Point2D& point);
