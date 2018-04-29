#include "stdafx.h"
#include "CompositeOutlineStyle.h"
#include "ICompositeShape.h"

CompositeOutlineStyle::CompositeOutlineStyle(ICompositeShape& composite)
	: m_composite(composite)
{
}

boost::optional<bool> CompositeOutlineStyle::IsEnabled() const
{
	if (m_composite.GetShapesCount() == 0u)
	{
		return boost::none;
	}

	boost::optional<bool> enabled = m_composite.GetShape(0)->GetOutlineStyle().IsEnabled();
	for (size_t i = 1; i < m_composite.GetShapesCount(); ++i)
	{
		if (m_composite.GetShape(i)->GetOutlineStyle().IsEnabled() != enabled)
		{
			return boost::none;
		}
	}
	return enabled;
}

void CompositeOutlineStyle::Enable(bool enable)
{
	for (size_t i = 0; i < m_composite.GetShapesCount(); ++i)
	{
		m_composite.GetShape(i)->GetOutlineStyle().Enable(enable);
	}
}

boost::optional<uint32_t> CompositeOutlineStyle::GetColor() const
{
	if (m_composite.GetShapesCount() == 0u)
	{
		return boost::none;
	}

	boost::optional<uint32_t> color = m_composite.GetShape(0)->GetOutlineStyle().GetColor();
	for (size_t i = 1; i < m_composite.GetShapesCount(); ++i)
	{
		if (m_composite.GetShape(i)->GetOutlineStyle().GetColor() != color)
		{
			return boost::none;
		}
	}
	return color;
}

void CompositeOutlineStyle::SetColor(uint32_t color)
{
	for (size_t i = 0; i < m_composite.GetShapesCount(); ++i)
	{
		m_composite.GetShape(i)->GetOutlineStyle().SetColor(color);
	}
}

boost::optional<unsigned> CompositeOutlineStyle::GetThickness() const
{
	if (m_composite.GetShapesCount() == 0u)
	{
		return boost::none;
	}

	boost::optional<unsigned> thickness = m_composite.GetShape(0)->GetOutlineStyle().GetThickness();
	for (size_t i = 1; i < m_composite.GetShapesCount(); ++i)
	{
		if (m_composite.GetShape(i)->GetOutlineStyle().GetThickness() != thickness)
		{
			return boost::none;
		}
	}
	return thickness;
}

void CompositeOutlineStyle::SetThickness(unsigned thickness)
{
	for (size_t i = 0; i < m_composite.GetShapesCount(); ++i)
	{
		m_composite.GetShape(i)->GetOutlineStyle().SetThickness(thickness);
	}
}
