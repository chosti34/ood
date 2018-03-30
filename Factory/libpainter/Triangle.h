#pragma once
#include "Shape.h"
#include "Point2D.h"

class Triangle : public Shape
{
public:
	Triangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Color& color);

	void Draw(ICanvas& canvas)const override;

	Point2D GetVertex1()const;
	Point2D GetVertex2()const;
	Point2D GetVertex3()const;

private:
	Point2D m_p1;
	Point2D m_p2;
	Point2D m_p3;
};
