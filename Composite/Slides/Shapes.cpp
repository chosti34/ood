#include "stdafx.h"
#include "Shapes.h"

void Shapes::InsertShape(const std::shared_ptr<IShape>& shape, size_t index)
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

void Shapes::RemoveShape(size_t index)
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

std::shared_ptr<IShape> Shapes::GetShape(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index must be less than shapes count");
	}
	return m_shapes[index];
}

std::shared_ptr<const IShape> Shapes::GetShape(size_t index)const
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index must be less than shapes count");
	}
	return m_shapes[index];
}

size_t Shapes::GetShapesCount()const
{
	return m_shapes.size();
}
