#include "stdafx.h"
#include "Slide.h"
#include "IShape.h"

Slide::Slide(float width, float height, uint32_t backgroundColor)
	: m_width(width)
	, m_height(height)
	, m_backgroundColor(backgroundColor)
{
}

void Slide::Draw(ICanvas& canvas)const
{
	for (size_t i = 0; i < m_shapes.GetShapesCount(); ++i)
	{
		m_shapes.GetShape(i)->Draw(canvas);
	}
}

float Slide::GetWidth()const
{
	return m_width;
}

float Slide::GetHeight()const
{
	return m_height;
}

IShapeCollection& Slide::GetShapes()
{
	return m_shapes;
}

const IShapeCollection& Slide::GetShapes()const
{
	return m_shapes;
}
