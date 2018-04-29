#include "stdafx.h"
#include "Shape.h"
#include "ShapeStyle.h"

Shape::Shape()
	: m_fillStyle(std::make_unique<ShapeStyle>())
	, m_outlineStyle(std::make_unique<ShapeStyle>())
{
}

void Shape::Draw(ICanvas& canvas)const
{
	if (m_outlineStyle->IsEnabled())
	{
		canvas.SetOutlineThickness(*m_outlineStyle->GetThickness());
		canvas.SetOutlineColor(*m_outlineStyle->GetColor());
		StrokeDrawImpl(canvas);
	}
	if (m_fillStyle->IsEnabled())
	{
		canvas.SetFillColor(*m_fillStyle->GetColor());
		FillDrawImpl(canvas);
	}
}

RectF Shape::GetFrame()const
{
	return RectF();
}

void Shape::SetFrame(const RectF& frame)
{
	(void)frame;
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

IShapeComposite* Shape::GetComposite()
{
	return nullptr;
}

const IShapeComposite* Shape::GetComposite()const
{
	return nullptr;
}
