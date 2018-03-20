#include "stdafx.h"
#include "Rectangle.h"

Rectangle::Rectangle(const Point& leftTop, const Point& rightBottom, const Color& color)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, Shape(color)
{
}

void Rectangle::Draw(ICanvas& canvas) const
{
	const float width = m_rightBottom.x - m_leftTop.x;
	const float height = m_rightBottom.y - m_rightBottom.x;

	const Point rightTop = { m_leftTop.x + width, m_leftTop.y };
	const Point leftBottom = { m_leftTop.x, m_leftTop.y + height };

	canvas.SetColor(GetColor());
	canvas.DrawLine(m_leftTop, rightTop);
	canvas.DrawLine(rightTop, m_rightBottom);
	canvas.DrawLine(m_rightBottom, leftBottom);
	canvas.DrawLine(leftBottom, m_leftTop);
}
