#pragma once
#include "Shape.h"
#include "Point.h"

class Rectangle : public Shape
{
public:
	Rectangle(const Point& leftTop, const Point& rightBottom, const Color& color);

	void Draw(ICanvas& canvas)const override;

private:
	Point m_leftTop;
	Point m_rightBottom;
};
