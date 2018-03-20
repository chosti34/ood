#include "stdafx.h"
#include "Ellipse.h"

Ellipse::Ellipse(const Point &center, float horizontalRadius, float verticalRadius, const Color& color)
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
	, Shape(color)
{
}

void Ellipse::Draw(ICanvas& canvas)const
{
	canvas.SetColor(GetColor());
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}

Point Ellipse::GetCenter()const
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
