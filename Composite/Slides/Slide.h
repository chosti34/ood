#pragma once
#include "ISlide.h"
#include "ShapeCollection.h"

class Slide : public ISlide
{
public:
	Slide(float width, float height, uint32_t backgroundColor = std::numeric_limits<uint32_t>::max());

	void Draw(ICanvas& canvas)const override;

	float GetWidth()const override;
	float GetHeight()const override;

	IShapeCollection& GetShapes() override;
	const IShapeCollection& GetShapes()const override;

private:
	float m_width;
	float m_height;
	uint32_t m_backgroundColor;
	ShapeCollection m_shapes;
};
