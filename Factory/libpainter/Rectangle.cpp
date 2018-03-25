#include "stdafx.h"
#include "Rectangle.h"

Rectangle::Rectangle(const Point& leftTop, const Point& rightBottom, const Color& color)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, Shape(color)
{
}

void Rectangle::Draw(ICanvas& canvas)const
{
	canvas.SetColor(GetColor());
	canvas.DrawLine(m_leftTop, Point{ m_rightBottom.x, m_leftTop.y });
	canvas.DrawLine(Point{ m_rightBottom.x, m_leftTop.y }, m_rightBottom);
	canvas.DrawLine(m_rightBottom, Point{ m_leftTop.x, m_rightBottom.y });
	canvas.DrawLine(Point{ m_leftTop.x, m_rightBottom.y }, m_leftTop);
}

Point Rectangle::GetLeftTop()const
{
	return m_leftTop;
}

Point Rectangle::GetRightBottom()const
{
	return m_rightBottom;
}
