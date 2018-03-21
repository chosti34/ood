#include "stdafx.h"
#include "PictureDraft.h"
#include "Shape.h"

bool PictureDraft::IsEmpty()const
{
	return m_shapes.empty();
}

void PictureDraft::AddShape(std::unique_ptr<Shape>&& shape)
{
	m_shapes.push_back(std::move(shape));
}
