#include "stdafx.h"
#include "Point2D.h"

bool operator ==(const Point2D& lhs, const Point2D& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::istream& operator >>(std::istream& strm, Point2D& point)
{
	strm >> point.x;
	strm >> point.y;
	return strm;
}
