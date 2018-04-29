#pragma once
#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(const Point2D& center, float horizontalRadius, float verticalRadius);

	const Point2D& GetCenter()const;
	float GetHorizontalRadius()const;
	float GetVerticalRadius()const;

private:
	void StrokeDrawImpl(ICanvas& canvas)const override;
	void FillDrawImpl(ICanvas& canvas)const override;

private:
	Point2D m_center;
	float m_horizontalRadius;
	float m_verticalRadius;
};
