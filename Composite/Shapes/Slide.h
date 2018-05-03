#pragma once
#include "ISlide.h"
#include "ShapeCollection.h"

class Slide : public ISlide
{
public:
	Slide(float width, float height, uint32_t backgroundColor);

	void Draw(ICanvas& canvas)const override;

	float GetWidth()const override;
	float GetHeight()const override;

	IShapeCollection& GetShapes() override;

private:
	float m_width;
	float m_height;
	uint32_t m_backgroundColor;
	ShapeCollection m_shapes;
};
