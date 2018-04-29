#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(const Point2D& leftTop, float width, float height);

	const Point2D& GetLeftTop()const;
	float GetWidth()const;
	float GetHeight()const;

private:
	void StrokeDrawImpl(ICanvas& canvas)const override;
	void FillDrawImpl(ICanvas& canvas)const override;

private:
	Point2D m_leftTop;
	float m_width;
	float m_height;
};
