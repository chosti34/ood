#include "stdafx.h"
#include "RegularPolygon.h"

namespace
{
std::vector<Point> GetRegularPolygonPoints(const Point& center, float radius, unsigned count)
{
	std::vector<Point> points(count);
	for (size_t i = 0; i < points.size(); ++i)
	{
		points[i].x = float(center.x + radius * std::cos(2 * M_PI * i / count));
		points[i].y = float(center.y + radius * std::sin(2 * M_PI * i / count));
	}
	return points;
}
}

RegularPolygon::RegularPolygon(const Point& center, float radius, unsigned vertexCount, const Color& color)
	: m_center(center)
	, m_radius(radius)
	, m_vertexCount(vertexCount)
	, Shape(color)
{
	assert(m_vertexCount >= 3u);
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

Point RegularPolygon::GetCenter()const
{
	return m_center;
}

float RegularPolygon::GetRadius()const
{
	return m_radius;
}
