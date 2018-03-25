#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3, const Color& color)
	: m_p1(p1)
	, m_p2(p2)
	, m_p3(p3)
	, Shape(color)
{
}

void Triangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawLine(m_p1, m_p2);
	canvas.DrawLine(m_p2, m_p3);
	canvas.DrawLine(m_p3, m_p1);
}

Point Triangle::GetVertex1()const
{
	return m_p1;
}

Point Triangle::GetVertex2()const
{
	return m_p2;
}

Point Triangle::GetVertex3()const
{
	return m_p3;
}
