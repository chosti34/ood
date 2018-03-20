#pragma once
#include "Shape.h"

class RegularPolygon : public Shape
{
public:
	RegularPolygon(const Point& center, float radius, unsigned vertexCount, const Color& color);

	void Draw(ICanvas& canvas)const override;

	unsigned GetVertexCount()const;
	Point GetCenter()const;
	float GetRadius()const;

private:
	Point m_center;
	float m_radius;
	unsigned m_vertexCount;
};
