#include "stdafx.h"
#include "PictureDraft.h"
#include "Shape.h"

PictureDraft::ConstIterator PictureDraft::begin()const
{
	return m_shapes.begin();
}

PictureDraft::ConstIterator PictureDraft::end()const
{
	return m_shapes.end();
}

bool PictureDraft::IsEmpty()const
{
	return m_shapes.empty();
}

void PictureDraft::AddShape(std::unique_ptr<Shape>&& shape)
{
	m_shapes.push_back(std::move(shape));
}
