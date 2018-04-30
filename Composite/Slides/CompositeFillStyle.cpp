#include "stdafx.h"
#include "CompositeFillStyle.h"
#include "ICompositeShape.h"
#include "GetCompositePropertyValue.h"

CompositeFillStyle::CompositeFillStyle(ICompositeShape& composite)
	: m_composite(composite)
{
}

boost::optional<bool> CompositeFillStyle::IsEnabled()const
{
	return GetCompositePropertyValueIfChildrenAreSame<bool>(m_composite.GetShapesCount(), [this](size_t index) {
		return m_composite.GetShape(index)->GetFillStyle().IsEnabled();
	});
}

void CompositeFillStyle::Enable(bool enable)
{
	for (size_t i = 0; i < m_composite.GetShapesCount(); ++i)
	{
		m_composite.GetShape(i)->GetFillStyle().Enable(enable);
	}
}

boost::optional<uint32_t> CompositeFillStyle::GetColor()const
{
	return GetCompositePropertyValueIfChildrenAreSame<uint32_t>(m_composite.GetShapesCount(), [this](size_t index) {
		return m_composite.GetShape(index)->GetFillStyle().GetColor();
	});
}

void CompositeFillStyle::SetColor(uint32_t color)
{
	for (size_t i = 0; i < m_composite.GetShapesCount(); ++i)
	{
		m_composite.GetShape(i)->GetFillStyle().SetColor(color);
	}
}
