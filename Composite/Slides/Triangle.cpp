#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle(const Point2D& vertex1, const Point2D& vertex2, const Point2D& vertex3)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

const Point2D Triangle::GetVertex1()const
{
	return m_vertex1;
}

const Point2D Triangle::GetVertex2()const
{
	return m_vertex2;
}

const Point2D Triangle::GetVertex3()const
{
	return m_vertex3;
}

void Triangle::StrokeDrawImpl(ICanvas& canvas)const
{
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}

void Triangle::FillDrawImpl(ICanvas& canvas)const
{
	canvas.FillPolygon({ m_vertex1, m_vertex2, m_vertex3 });
}
