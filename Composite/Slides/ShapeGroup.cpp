#include "stdafx.h"
#include "ShapeGroup.h"
#include "ShapeStyle.h"

ShapeGroup::ShapeGroup()
	: m_fillStyle(std::make_unique<ShapeStyle>())
	, m_outlineStyle(std::make_unique<ShapeStyle>())
{
}

void ShapeGroup::Draw(ICanvas& canvas)const
{
	for (const auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

RectF ShapeGroup::GetFrame()const
{
	// вернуть прямоугольник, ограничивающий находящиеся внутри группы фигуры
	return RectF();
}

void ShapeGroup::SetFrame(const RectF& frame)
{
	// изменить координаты и размеры фигур внутри группы
	//  пропорционально их координатам и размерам внутри фигуры
}

IShapeStyle& ShapeGroup::GetFillStyle()
{
	return *m_fillStyle;
}

const IShapeStyle& ShapeGroup::GetFillStyle()const
{
	return *m_fillStyle;
}

IShapeStyle& ShapeGroup::GetOutlineStyle()
{
	return *m_outlineStyle;
}

const IShapeStyle& ShapeGroup::GetOutlineStyle()const
{
	return *m_outlineStyle;
}

IShapeGroup* ShapeGroup::GetGroup()
{
	return this;
}

const IShapeGroup* ShapeGroup::GetGroup()const
{
	return this;
}

void ShapeGroup::InsertShape(const std::shared_ptr<IShape>& shape, size_t index)
{
	if (index >= m_shapes.size())
	{
		m_shapes.push_back(std::move(shape));
	}
	else
	{
		m_shapes.insert(m_shapes.begin() + index, std::move(shape));
	}
}

void ShapeGroup::RemoveShape(size_t index)
{
	if (m_shapes.empty())
	{
		throw std::out_of_range("Slide has no shapes to remove");
	}

	if (index >= m_shapes.size())
	{
		m_shapes.pop_back();
	}
	else
	{
		m_shapes.erase(m_shapes.begin() + index);
	}
}

std::shared_ptr<IShape> ShapeGroup::GetShape(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index must be less than shapes count");
	}
	return m_shapes[index];
}

std::shared_ptr<const IShape> ShapeGroup::GetShape(size_t index)const
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index must be less than shapes count");
	}
	return m_shapes[index];
}

size_t ShapeGroup::GetShapesCount()const
{
	return m_shapes.size();
}
