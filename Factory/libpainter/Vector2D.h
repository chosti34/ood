#pragma once
#include "Point2D.h"

struct Vector2D
{
	Vector2D() = default;
	Vector2D(float x, float y);
	Vector2D(const Point2D& from, const Point2D& to);

	float GetLength()const;

	float x;
	float y;
};

bool operator ==(const Vector2D& lhs, const Vector2D& rhs);
