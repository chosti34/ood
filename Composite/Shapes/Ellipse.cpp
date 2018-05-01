#include "stdafx.h"
#include "Ellipse.h"

Ellipse::Ellipse(const Point2D& center, float horizontalRadius, float verticalRadius)
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
}

RectF Ellipse::GetFrame()const
{
	Point2D leftTop = { m_center.x - m_horizontalRadius, m_center.y - m_verticalRadius };
	return RectF{ leftTop.x, leftTop.y, 2 * m_horizontalRadius, 2 * m_verticalRadius };
}

void Ellipse::SetFrame(const RectF& frame)
{
	m_center.x = frame.left + frame.width / 2;
	m_center.y = frame.top + frame.height / 2;
	m_horizontalRadius = frame.width / 2;
	m_verticalRadius = frame.height / 2;
}

const Point2D& Ellipse::GetCenter()const
{
	return m_center;
}

float Ellipse::GetHorizontalRadius()const
{
	return m_horizontalRadius;
}

float Ellipse::GetVerticalRadius()const
{
	return m_verticalRadius;
}

void Ellipse::StrokeDrawImpl(ICanvas& canvas)const
{
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}

void Ellipse::FillDrawImpl(ICanvas& canvas)const
{
	canvas.FillEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}
