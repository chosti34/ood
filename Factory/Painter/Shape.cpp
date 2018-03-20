#include "stdafx.h"
#include "Shape.h"

Shape::Shape(const Color& color)
	: m_color(color)
{
}

Color Shape::GetColor()const
{
	return m_color;
}
