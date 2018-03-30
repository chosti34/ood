#pragma once
#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(const Point2D& center, float horizontalRadius, float verticalRadius, const Color& color);

	void Draw(ICanvas& canvas)const override;

	Point2D GetCenter()const;
	float GetHorizontalRadius()const;
	float GetVerticalRadius()const;

private:
	Point2D m_center;
	float m_horizontalRadius;
	float m_verticalRadius;
};
