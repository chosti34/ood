#include "stdafx.h"
#include "CompositeOutlineStyle.h"
#include "ICompositeShape.h"
#include "GetCompositePropertyValue.h"

CompositeOutlineStyle::CompositeOutlineStyle(ICompositeShape& composite)
	: m_composite(composite)
{
}

boost::optional<bool> CompositeOutlineStyle::IsEnabled()const
{
	return GetCompositePropertyValueIfChildrenAreSame<bool>(m_composite.GetShapesCount(), [this](size_t index) {
		return m_composite.GetShape(index)->GetOutlineStyle().IsEnabled();
	});
}

void CompositeOutlineStyle::Enable(bool enable)
{
	for (size_t i = 0; i < m_composite.GetShapesCount(); ++i)
	{
		m_composite.GetShape(i)->GetOutlineStyle().Enable(enable);
	}
}

boost::optional<uint32_t> CompositeOutlineStyle::GetColor()const
{
	return GetCompositePropertyValueIfChildrenAreSame<uint32_t>(m_composite.GetShapesCount(), [this](size_t index) {
		return m_composite.GetShape(index)->GetOutlineStyle().GetColor();
	});
}

void CompositeOutlineStyle::SetColor(uint32_t color)
{
	for (size_t i = 0; i < m_composite.GetShapesCount(); ++i)
	{
		m_composite.GetShape(i)->GetOutlineStyle().SetColor(color);
	}
}

boost::optional<unsigned> CompositeOutlineStyle::GetThickness()const
{
	return GetCompositePropertyValueIfChildrenAreSame<unsigned>(m_composite.GetShapesCount(), [this](size_t index) {
		return m_composite.GetShape(index)->GetOutlineStyle().GetThickness();
	});
}

void CompositeOutlineStyle::SetThickness(unsigned thickness)
{
	for (size_t i = 0; i < m_composite.GetShapesCount(); ++i)
	{
		m_composite.GetShape(i)->GetOutlineStyle().SetThickness(thickness);
	}
}
