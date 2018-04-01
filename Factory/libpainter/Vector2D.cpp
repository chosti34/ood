#include "stdafx.h"
#include "Vector2D.h"

Vector2D::Vector2D(const Point2D& from, const Point2D& to)
	: x(to.x -from.x)
	, y(to.y - from.y)
{
}

Vector2D::Vector2D(float x, float y)
	: x(x)
	, y(y)
{
}

float Vector2D::GetLength() const
{
	return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

bool operator ==(const Vector2D& lhs, const Vector2D& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
