#include "stdafx.h"
#include "Shape.h"
#include "ShapeStyle.h"

Shape::Shape()
	: m_fillStyle(std::make_unique<ShapeStyle>())
	, m_outlineStyle(std::make_unique<ShapeStyle>())
{
}

RectF Shape::GetFrame() const
{
	return RectF();
}

void Shape::SetFrame(const RectF& frame)
{
}

IShapeStyle& Shape::GetFillStyle()
{
	return *m_fillStyle;
}

const IShapeStyle& Shape::GetFillStyle()const
{
	return *m_fillStyle;
}

IShapeStyle& Shape::GetOutlineStyle()
{
	return *m_outlineStyle;
}

const IShapeStyle& Shape::GetOutlineStyle()const
{
	return *m_outlineStyle;
}

IShapeGroup* Shape::GetGroup()
{
	return nullptr;
}

const IShapeGroup* Shape::GetGroup()const
{
	return nullptr;
}
