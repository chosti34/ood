#pragma once
#include "Shape.h"

class RegularPolygon : public Shape
{
public:
	RegularPolygon(const Point2D& center, float radius, unsigned vertexCount, const Color& color);

	void Draw(ICanvas& canvas)const override;

	unsigned GetVertexCount()const;
	Point2D GetCenter()const;
	float GetRadius()const;

private:
	Point2D m_center;
	float m_radius;
	unsigned m_vertexCount;
};
