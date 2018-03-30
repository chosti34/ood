#include "stdafx.h"
#include "Ellipse.h"

Ellipse::Ellipse(const Point2D &center, float horizontalRadius, float verticalRadius, const Color& color)
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
	, Shape(color)
{
	if (m_horizontalRadius < 0 || m_verticalRadius < 0)
	{
		throw std::invalid_argument("can't construct ellipse");
	}
}

void Ellipse::Draw(ICanvas& canvas)const
{
	canvas.SetColor(GetColor());
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}

Point2D Ellipse::GetCenter()const
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
