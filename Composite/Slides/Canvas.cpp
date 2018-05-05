#include "stdafx.h"
#include "Canvas.h"
#include "../Shapes/Color.h"

namespace
{
std::vector<Gdiplus::PointF> ToGdiplusPoints(const std::vector<Point2D>& points)
{
	std::vector<Gdiplus::PointF> gdiPoints(points.size());
	std::transform(points.begin(), points.end(), gdiPoints.begin(), [](auto&& point) {
		return Gdiplus::PointF{ point.x, point.y };
	});
	return gdiPoints;
}
}

Canvas::Canvas(Gdiplus::Graphics& gfx)
	: m_gfx(gfx)
	, m_pen(Gdiplus::Color())
	, m_brush(Gdiplus::Color())
{
	m_pen.SetLineJoin(Gdiplus::LineJoinRound);
}

void Canvas::DrawLine(const Point2D& from, const Point2D& to)
{
	m_gfx.DrawLine(&m_pen, Gdiplus::PointF(from.x, from.y), Gdiplus::PointF(to.x, to.y));
}

void Canvas::FillPolygon(const std::vector<Point2D>& points)
{
	const std::vector<Gdiplus::PointF> gdiplusPoints = ToGdiplusPoints(points);
	m_gfx.FillPolygon(&m_brush, gdiplusPoints.data(), points.size());
}

void Canvas::DrawEllipse(const Point2D& center, float horizontalRadius, float verticalRadius)
{
	m_gfx.DrawEllipse(&m_pen, Gdiplus::RectF(
		center.x - horizontalRadius,
		center.y - verticalRadius,
		2 * horizontalRadius,
		2 * verticalRadius));
}

void Canvas::FillEllipse(const Point2D& center, float horizontalRadius, float verticalRadius)
{
	m_gfx.FillEllipse(&m_brush, Gdiplus::RectF(
		center.x - horizontalRadius,
		center.y - verticalRadius,
		2 * horizontalRadius,
		2 * verticalRadius));
}

void Canvas::SetFillColor(uint32_t fillColor)
{
	const RGBAColor rgba = GetColorComponents(fillColor);
	m_brush.SetColor(Gdiplus::Color(rgba.a, rgba.r, rgba.g, rgba.b));
}

void Canvas::SetOutlineColor(uint32_t outlineColor)
{
	const RGBAColor rgba = GetColorComponents(outlineColor);
	m_pen.SetColor(Gdiplus::Color(rgba.a, rgba.r, rgba.g, rgba.b));
}

void Canvas::SetOutlineThickness(float thickness)
{
	m_pen.SetWidth(thickness);
}
