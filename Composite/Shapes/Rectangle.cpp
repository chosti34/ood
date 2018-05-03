#include "stdafx.h"
#include "Rectangle.h"

using namespace shapelib;

namespace
{
std::vector<Point2D> GetRectangleBoundingPoints(const Point2D& leftTop, float width, float height)
{
	return {
		leftTop,
		{ leftTop.x + width, leftTop.y },
		{ leftTop.x + width, leftTop.y + height },
		{ leftTop.x, leftTop.y + height }
	};
}
}

Rectangle::Rectangle(const Point2D& leftTop, float width, float height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

RectF Rectangle::GetFrame()const
{
	return RectF{ m_leftTop.x, m_leftTop.y, m_width, m_height };
}

void Rectangle::SetFrame(const RectF& frame)
{
	m_leftTop = { frame.left, frame.top };
	m_width = frame.width;
	m_height = frame.height;
}

const Point2D& Rectangle::GetLeftTop()const
{
	return m_leftTop;
}

float Rectangle::GetWidth()const
{
	return m_width;
}

float Rectangle::GetHeight()const
{
	return m_height;
}

void Rectangle::StrokeDrawImpl(ICanvas& canvas)const
{
	auto points = GetRectangleBoundingPoints(m_leftTop, m_width, m_height);
	canvas.DrawLine(points[0], points[1]);
	canvas.DrawLine(points[1], points[2]);
	canvas.DrawLine(points[2], points[3]);
	canvas.DrawLine(points[3], points[0]);
}

void Rectangle::FillDrawImpl(ICanvas& canvas)const
{
	canvas.FillPolygon(GetRectangleBoundingPoints(m_leftTop, m_width, m_height));
}
