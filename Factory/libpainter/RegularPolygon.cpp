#include "stdafx.h"
#include "RegularPolygon.h"

namespace
{
std::vector<Point2D> GetRegularPolygonPoints(const Point2D& center, float radius, unsigned count)
{
	std::vector<Point2D> points(count);
	for (size_t i = 0; i < points.size(); ++i)
	{
		points[i].x = float(center.x + radius * std::cos(2 * M_PI * i / count));
		points[i].y = float(center.y + radius * std::sin(2 * M_PI * i / count));
	}
	return points;
}
}

RegularPolygon::RegularPolygon(const Point2D& center, float radius, unsigned vertexCount, const Color& color)
	: m_center(center)
	, m_radius(radius)
	, m_vertexCount(vertexCount)
	, Shape(color)
{
	if (radius < 0 || vertexCount < 3)
	{
		throw std::invalid_argument("can't construct regular polygon");
	}
}

void RegularPolygon::Draw(ICanvas& canvas)const
{
	const auto points = GetRegularPolygonPoints(m_center, m_radius, m_vertexCount);
	canvas.SetColor(GetColor());
	for (size_t i = 0; i < points.size() - 1; ++i)
	{
		canvas.DrawLine(points[i], points[i + 1]);
	}
	canvas.DrawLine(points.back(), points.front());
}

unsigned RegularPolygon::GetVertexCount()const
{
	return m_vertexCount;
}

Point2D RegularPolygon::GetCenter()const
{
	return m_center;
}

float RegularPolygon::GetRadius()const
{
	return m_radius;
}
