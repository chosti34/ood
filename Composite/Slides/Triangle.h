#pragma once
#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle(const Point2D& vertex1, const Point2D& vertex2, const Point2D& vertex3);

	const Point2D GetVertex1()const;
	const Point2D GetVertex2()const;
	const Point2D GetVertex3()const;

private:
	virtual void StrokeDrawImpl(ICanvas& canvas)const override;
	virtual void FillDrawImpl(ICanvas& canvas)const override;

private:
	Point2D m_vertex1;
	Point2D m_vertex2;
	Point2D m_vertex3;
};
