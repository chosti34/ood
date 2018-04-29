#pragma once
#include "Point2D.h"
#include <cstdint>
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void DrawLine(const Point2D& from, const Point2D& to) = 0;
	virtual void FillPolygon(const std::vector<Point2D>& points) = 0;

	virtual void DrawEllipse(const Point2D& center, float horizontalRadius, float verticalRadius) = 0;
	virtual void FillEllipse(const Point2D& center, float horizontalRadius, float verticalRadius) = 0;

	virtual void SetFillColor(uint32_t fillColor) = 0;
	virtual void SetOutlineColor(uint32_t outlineColor) = 0;
	virtual void SetOutlineThickness(unsigned thickness) = 0;
};
