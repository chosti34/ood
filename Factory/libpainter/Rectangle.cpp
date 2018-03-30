#include "stdafx.h"
#include "Rectangle.h"
#include "Vector2D.h"

Rectangle::Rectangle(const Point2D& leftTop, const Point2D& rightBottom, const Color& color)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, Shape(color)
{
	Vector2D diag(leftTop, rightBottom);
	if (diag.x <= 0 || diag.y <= 0)
	{
		throw std::invalid_argument("can't construct rectangle");
	}
}

void Rectangle::Draw(ICanvas& canvas)const
{
	canvas.SetColor(GetColor());
	canvas.DrawLine(m_leftTop, Point2D{ m_rightBottom.x, m_leftTop.y });
	canvas.DrawLine(Point2D{ m_rightBottom.x, m_leftTop.y }, m_rightBottom);
	canvas.DrawLine(m_rightBottom, Point2D{ m_leftTop.x, m_rightBottom.y });
	canvas.DrawLine(Point2D{ m_leftTop.x, m_rightBottom.y }, m_leftTop);
}

Point2D Rectangle::GetLeftTop()const
{
	return m_leftTop;
}

Point2D Rectangle::GetRightBottom()const
{
	return m_rightBottom;
}
