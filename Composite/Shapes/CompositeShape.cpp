#include "stdafx.h"
#include "CompositeShape.h"
#include "CompositeOutlineStyle.h"
#include "CompositeFillStyle.h"
#include "StyleEnumerator.h"

CompositeShape::CompositeShape()
{
	m_fillStyle = std::make_unique<CompositeFillStyle>([this](StyleCallback<IFillStyle>&& callback) {
		for (size_t i = 0; i < m_shapes.GetShapesCount(); ++i)
		{
			callback(m_shapes.GetShape(i)->GetFillStyle());
		}
	});
	m_outlineStyle = std::make_unique<CompositeOutlineStyle>([this](StyleCallback<IOutlineStyle>&& callback) {
		for (size_t i = 0; i < m_shapes.GetShapesCount(); ++i)
		{
			callback(m_shapes.GetShape(i)->GetOutlineStyle());
		}
	});
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
	if (m_shapes.GetShapesCount() == 0)
	{
		throw std::logic_error("can't get frame of empty composite shape");
	}

	auto innerFrame = m_shapes.GetShape(0)->GetFrame();
	float minX = innerFrame.left;
	float minY = innerFrame.top;
	float maxX = innerFrame.left + innerFrame.width;
	float maxY = innerFrame.top + innerFrame.height;

	for (size_t i = 1; i < m_shapes.GetShapesCount(); ++i)
	{
		innerFrame = m_shapes.GetShape(i)->GetFrame();
		if (innerFrame.left < minX)
		{
			minX = innerFrame.left;
		}
		if (innerFrame.top < minY)
		{
			minY = innerFrame.top;
		}
		if (innerFrame.left + innerFrame.width > maxX)
		{
			maxX = innerFrame.left + innerFrame.width;
		}
		if (innerFrame.top + innerFrame.height > maxY)
		{
			maxY = innerFrame.top + innerFrame.height;
		}
	}
	return RectF{ minX, minY, maxX - minX, maxY - minY };
}

void CompositeShape::SetFrame(const RectF& frame)
{
	if (m_shapes.GetShapesCount() == 0)
	{
		throw std::logic_error("can't set frame to composite shape that has no children");
	}

	const auto oldCompositeFrame = GetFrame();
	const std::pair<float, float> percentage = {
		frame.width / oldCompositeFrame.width, frame.height / oldCompositeFrame.height };

	for (size_t i = 0; i < m_shapes.GetShapesCount(); ++i)
	{
		const auto oldInnerFrame = m_shapes.GetShape(i)->GetFrame();
		const float newX = frame.left + (oldInnerFrame.left - oldCompositeFrame.left) * percentage.first;
		const float newY = frame.top + (oldInnerFrame.top - oldCompositeFrame.top) * percentage.second;
		m_shapes.GetShape(i)->SetFrame(RectF{
			newX,
			newY,
			oldInnerFrame.width * percentage.first,
			oldInnerFrame.height * percentage.second});
	}
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
