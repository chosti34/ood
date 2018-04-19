#pragma once
#include "Point.h"
#include "ICanvasDrawable.h"

namespace shape_drawing_lib
{
class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point& p1, const Point& p2, const Point& p3, uint32_t color = 0);
	void Draw(graphics_lib::ICanvas& canvas)const override;

private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
	uint32_t m_color;
};
}
