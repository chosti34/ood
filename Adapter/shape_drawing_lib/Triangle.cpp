#include "stdafx.h"
#include "Triangle.h"

using namespace shape_drawing_lib;

CTriangle::CTriangle(const Point& p1, const Point& p2, const Point& p3, uint32_t color)
	: m_p1(p1)
	, m_p2(p2)
	, m_p3(p3)
	, m_color(color)
{
}

void CTriangle::Draw(graphics_lib::ICanvas& canvas)const
{
	canvas.SetColor(m_color);
	canvas.MoveTo(m_p1.x, m_p1.y);
	canvas.LineTo(m_p2.x, m_p2.y);
	canvas.LineTo(m_p3.x, m_p3.y);
	canvas.LineTo(m_p1.x, m_p1.y);
}
