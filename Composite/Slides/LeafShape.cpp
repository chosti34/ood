#include "stdafx.h"
#include "LeafShape.h"
#include "LeafOutlineStyle.h"
#include "LeafFillStyle.h"

LeafShape::LeafShape()
	: m_fillStyle(std::make_unique<LeafFillStyle>())
	, m_outlineStyle(std::make_unique<LeafOutlineStyle>())
{
}

LeafShape::~LeafShape()
{
}

void LeafShape::Draw(ICanvas& canvas)const
{
	if (*m_outlineStyle->IsEnabled())
	{
		canvas.SetOutlineThickness(*m_outlineStyle->GetThickness());
		canvas.SetOutlineColor(*m_outlineStyle->GetColor());
		StrokeDrawImpl(canvas);
	}
	if (*m_fillStyle->IsEnabled())
	{
		canvas.SetFillColor(*m_fillStyle->GetColor());
		FillDrawImpl(canvas);
	}
}

RectF LeafShape::GetFrame()const
{
	return RectF();
}

void LeafShape::SetFrame(const RectF& frame)
{
	(void)frame;
}

IFillStyle& LeafShape::GetFillStyle()
{
	return *m_fillStyle;
}

const IFillStyle& LeafShape::GetFillStyle()const
{
	return *m_fillStyle;
}

IOutlineStyle& LeafShape::GetOutlineStyle()
{
	return *m_outlineStyle;
}

const IOutlineStyle& LeafShape::GetOutlineStyle()const
{
	return *m_outlineStyle;
}

ICompositeShape* LeafShape::GetComposite()
{
	return nullptr;
}

const ICompositeShape* LeafShape::GetComposite()const
{
	return nullptr;
}
