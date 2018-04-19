#pragma once
#include "Point.h"
#include "ICanvasDrawable.h"

namespace shape_drawing_lib
{
class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(const Point& leftTop, int width, int height, uint32_t color = 0);
	void Draw(graphics_lib::ICanvas& canvas)const override;

private:
	Point m_leftTop;
	int m_width;
	int m_height;
	uint32_t m_color;
};
}