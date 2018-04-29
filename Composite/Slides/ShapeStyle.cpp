#include "stdafx.h"
#include "ShapeStyle.h"

ShapeStyle::ShapeStyle(bool enabled, uint32_t color, unsigned thickness)
	: m_enabled(enabled)
	, m_color(color)
	, m_thickness(thickness)
{
}

boost::optional<bool> ShapeStyle::IsEnabled()const
{
	return m_enabled;
}

void ShapeStyle::Enable(bool enable)
{
	m_enabled = enable;
}

boost::optional<uint32_t> ShapeStyle::GetColor()const
{
	return m_color;
}

void ShapeStyle::SetColor(boost::optional<uint32_t> color)
{
	m_color = color;
}

boost::optional<unsigned> ShapeStyle::GetThickness()const
{
	return m_thickness;
}

void ShapeStyle::SetThickness(boost::optional<unsigned> thickness)
{
	m_thickness = thickness;
}
