#include "stdafx.h"
#include "ShapeCollection.h"

void ShapeCollection::InsertShape(const std::shared_ptr<IShape>& shape, size_t index)
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

void ShapeCollection::RemoveShape(size_t index)
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

std::shared_ptr<IShape> ShapeCollection::GetShape(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index must be less than shapes count");
	}
	return m_shapes[index];
}

std::shared_ptr<const IShape> ShapeCollection::GetShape(size_t index)const
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index must be less than shapes count");
	}
	return m_shapes[index];
}

size_t ShapeCollection::GetShapesCount()const
{
	return m_shapes.size();
}
