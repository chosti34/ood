#include "stdafx.h"
#include "LeafFillStyle.h"

LeafFillStyle::LeafFillStyle(bool enabled, uint32_t color)
	: m_enabled(enabled)
	, m_color(color)
{
}

boost::optional<bool> LeafFillStyle::IsEnabled() const
{
	return m_enabled;
}

void LeafFillStyle::Enable(bool enable)
{
	m_enabled = enable;
}

boost::optional<uint32_t> LeafFillStyle::GetColor() const
{
	return m_color;
}

void LeafFillStyle::SetColor(uint32_t color)
{
	m_color = color;
}
