#pragma once
#include "Shape.h"
#include "Point2D.h"

class Rectangle : public Shape
{
public:
	Rectangle(const Point2D& leftTop, const Point2D& rightBottom, const Color& color);

	void Draw(ICanvas& canvas)const override;

	Point2D GetLeftTop()const;
	Point2D GetRightBottom()const;

private:
	Point2D m_leftTop;
	Point2D m_rightBottom;
};
