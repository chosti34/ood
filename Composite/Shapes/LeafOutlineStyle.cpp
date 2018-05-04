#include "stdafx.h"
#include "LeafOutlineStyle.h"

LeafOutlineStyle::LeafOutlineStyle(bool enabled, uint32_t color, float thickness)
	: m_enabled(enabled)
	, m_color(color)
	, m_thickness(thickness)
{
}

boost::optional<bool> LeafOutlineStyle::IsEnabled()const
{
	return m_enabled;
}

void LeafOutlineStyle::Enable(bool enable)
{
	m_enabled = enable;
}

boost::optional<uint32_t> LeafOutlineStyle::GetColor()const
{
	return m_color;
}

void LeafOutlineStyle::SetColor(uint32_t color)
{
	m_color = color;
}

boost::optional<float> LeafOutlineStyle::GetThickness()const
{
	return m_thickness;
}

void LeafOutlineStyle::SetThickness(float thickness)
{
	m_thickness = thickness;
}
