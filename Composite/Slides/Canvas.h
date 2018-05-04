#pragma once
#include "../Shapes/ICanvas.h"
#include <gdiplusgraphics.h>

class Canvas : public ICanvas
{
public:
	Canvas(Gdiplus::Graphics& gfx);

	virtual void DrawLine(const Point2D& from, const Point2D& to) override;
	virtual void FillPolygon(const std::vector<Point2D>& points) override;
	virtual void DrawEllipse(const Point2D& center, float horizontalRadius, float verticalRadius) override;
	virtual void FillEllipse(const Point2D& center, float horizontalRadius, float verticalRadius) override;
	virtual void SetFillColor(uint32_t fillColor) override;
	virtual void SetOutlineColor(uint32_t outlineColor) override;
	virtual void SetOutlineThickness(float thickness) override;

private:
	Gdiplus::Graphics& m_gfx;
	Gdiplus::SolidBrush m_brush;
	Gdiplus::Pen m_pen;
};
