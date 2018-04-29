#include "stdafx.h"
#include "ShapeComposite.h"
#include "ShapeStyle.h"

ShapeComposite::ShapeComposite()
	: m_fillStyle(std::make_unique<ShapeStyle>())
	, m_outlineStyle(std::make_unique<ShapeStyle>())
{
}

void ShapeComposite::Draw(ICanvas& canvas)const
{
	for (size_t i = 0; i < m_shapes.GetShapesCount(); ++i)
	{
		m_shapes.GetShape(i)->Draw(canvas);
	}
}

RectF ShapeComposite::GetFrame()const
{
	// вернуть прямоугольник, ограничивающий находящиеся внутри группы фигуры
	return RectF();
}

void ShapeComposite::SetFrame(const RectF& frame)
{
	// изменить координаты и размеры фигур внутри группы
	//  пропорционально их координатам и размерам внутри фигуры
	(void)frame;
}

IShapeStyle& ShapeComposite::GetFillStyle()
{
	return *m_fillStyle;
}

const IShapeStyle& ShapeComposite::GetFillStyle()const
{
	return *m_fillStyle;
}

IShapeStyle& ShapeComposite::GetOutlineStyle()
{
	return *m_outlineStyle;
}

const IShapeStyle& ShapeComposite::GetOutlineStyle()const
{
	return *m_outlineStyle;
}

IShapeComposite* ShapeComposite::GetComposite()
{
	return this;
}

const IShapeComposite* ShapeComposite::GetComposite()const
{
	return this;
}

void ShapeComposite::InsertShape(const std::shared_ptr<IShape>& shape, size_t index)
{
	m_shapes.InsertShape(shape, index);
}

void ShapeComposite::RemoveShape(size_t index)
{
	m_shapes.RemoveShape(index);
}

std::shared_ptr<IShape> ShapeComposite::GetShape(size_t index)
{
	return m_shapes.GetShape(index);
}

std::shared_ptr<const IShape> ShapeComposite::GetShape(size_t index)const
{
	return m_shapes.GetShape(index);
}

size_t ShapeComposite::GetShapesCount()const
{
	return m_shapes.GetShapesCount();
}
