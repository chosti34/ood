#include "stdafx.h"
#include "CompositeShape.h"
#include "CompositeOutlineStyle.h"
#include "CompositeFillStyle.h"

CompositeShape::CompositeShape()
	: m_fillStyle(std::make_unique<CompositeFillStyle>(*this))
	, m_outlineStyle(std::make_unique<CompositeOutlineStyle>(*this))
{
}

void CompositeShape::Draw(ICanvas& canvas)const
{
	for (size_t i = 0; i < m_shapes.GetShapesCount(); ++i)
	{
		m_shapes.GetShape(i)->Draw(canvas);
	}
}

RectF CompositeShape::GetFrame()const
{
	// вернуть прямоугольник, ограничивающий находящиеся внутри группы фигуры
	return RectF();
}

void CompositeShape::SetFrame(const RectF& frame)
{
	// изменить координаты и размеры фигур внутри группы
	//  пропорционально их координатам и размерам внутри фигуры
	(void)frame;
}

IFillStyle& CompositeShape::GetFillStyle()
{
	return *m_fillStyle;
}

const IFillStyle& CompositeShape::GetFillStyle()const
{
	return *m_fillStyle;
}

IOutlineStyle& CompositeShape::GetOutlineStyle()
{
	return *m_outlineStyle;
}

const IOutlineStyle& CompositeShape::GetOutlineStyle()const
{
	return *m_outlineStyle;
}

ICompositeShape* CompositeShape::GetComposite()
{
	return this;
}

const ICompositeShape* CompositeShape::GetComposite()const
{
	return this;
}

void CompositeShape::InsertShape(const std::shared_ptr<IShape>& shape, size_t index)
{
	m_shapes.InsertShape(shape, index);
}

void CompositeShape::RemoveShape(size_t index)
{
	m_shapes.RemoveShape(index);
}

std::shared_ptr<IShape> CompositeShape::GetShape(size_t index)
{
	return m_shapes.GetShape(index);
}

std::shared_ptr<const IShape> CompositeShape::GetShape(size_t index)const
{
	return m_shapes.GetShape(index);
}

size_t CompositeShape::GetShapesCount()const
{
	return m_shapes.GetShapesCount();
}
