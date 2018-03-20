#pragma once
#include "Color.h"
#include "Point.h"

class ICanvas
{
public:
	virtual void SetColor(const Color& color) = 0;
	virtual void DrawLine(const Point& from, const Point& to) = 0;
	virtual void DrawEllipse(const Point& center, float a, float b) = 0;
};
