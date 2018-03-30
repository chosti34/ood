#pragma once
#include "Color.h"
#include "Point2D.h"

class ICanvas
{
public:
	virtual void SetColor(const Color& color) = 0;
	virtual void DrawLine(const Point2D& from, const Point2D& to) = 0;
	virtual void DrawEllipse(const Point2D& center, float horizontalRadius, float verticalRadius) = 0;
};
