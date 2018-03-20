#pragma once
#include "Shape.h"
#include "Point.h"

class Triangle : public Shape
{
public:
	Triangle(const Point& p1, const Point& p2, const Point& p3, const Color& color);

	void Draw(ICanvas& canvas)const override;

private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
};
