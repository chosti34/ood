#include "stdafx.h"
#include "Triangle.h"
#include "Vector2D.h"

Triangle::Triangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Color& color)
	: m_p1(p1)
	, m_p2(p2)
	, m_p3(p3)
	, Shape(color)
{
	float ab = Vector2D(m_p1, m_p2).GetLength();
	float bc = Vector2D(m_p2, m_p3).GetLength();
	float ac = Vector2D(m_p3, m_p1).GetLength();
	// Точки лежат на одной прямой
	if (ab == bc + ac || bc == ab + ac || ac == ab + bc)
	{
		throw std::invalid_argument("can't construct triangle");
	}
}

void Triangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawLine(m_p1, m_p2);
	canvas.DrawLine(m_p2, m_p3);
	canvas.DrawLine(m_p3, m_p1);
}

Point2D Triangle::GetVertex1()const
{
	return m_p1;
}

Point2D Triangle::GetVertex2()const
{
	return m_p2;
}

Point2D Triangle::GetVertex3()const
{
	return m_p3;
}
