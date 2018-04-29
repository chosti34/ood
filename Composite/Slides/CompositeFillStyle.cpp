#include "stdafx.h"
#include "CompositeFillStyle.h"
#include "ICompositeShape.h"

CompositeFillStyle::CompositeFillStyle(ICompositeShape& composite)
	: m_composite(composite)
{
}

boost::optional<bool> CompositeFillStyle::IsEnabled()const
{
	if (m_composite.GetShapesCount() == 0u)
	{
		return boost::none;
	}

	boost::optional<bool> enabled = m_composite.GetShape(0)->GetFillStyle().IsEnabled();
	for (size_t i = 1; i < m_composite.GetShapesCount(); ++i)
	{
		if (m_composite.GetShape(i)->GetFillStyle().IsEnabled() != enabled)
		{
			return boost::none;
		}
	}
	return enabled;
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
	if (m_composite.GetShapesCount() == 0u)
	{
		return boost::none;
	}

	boost::optional<uint32_t> color = m_composite.GetShape(0)->GetFillStyle().GetColor();
	for (size_t i = 1; i < m_composite.GetShapesCount(); ++i)
	{
		if (m_composite.GetShape(i)->GetFillStyle().GetColor() != color)
		{
			return boost::none;
		}
	}
	return color;
}

void CompositeFillStyle::SetColor(uint32_t color)
{
	for (size_t i = 0; i < m_composite.GetShapesCount(); ++i)
	{
		m_composite.GetShape(i)->GetFillStyle().SetColor(color);
	}
}
