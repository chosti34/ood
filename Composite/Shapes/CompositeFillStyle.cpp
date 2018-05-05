#include "stdafx.h"
#include "CompositeFillStyle.h"

CompositeFillStyle::CompositeFillStyle(StyleEnumerator<IFillStyle> && enumerate)
	: m_enumerate(enumerate)
{
}

boost::optional<bool> CompositeFillStyle::IsEnabled()const
{
	return GetValueIfAllSame<IFillStyle, bool>(m_enumerate, [](const IFillStyle& style) {
		return style.IsEnabled();
	});
}

void CompositeFillStyle::Enable(bool enable)
{
	m_enumerate([&enable](IFillStyle& style) {
		style.Enable(enable);
	});
}

boost::optional<uint32_t> CompositeFillStyle::GetColor()const
{
	return GetValueIfAllSame<IFillStyle, uint32_t>(m_enumerate, [](const IFillStyle& style) {
		return style.GetColor();
	});
}

void CompositeFillStyle::SetColor(uint32_t color)
{
	m_enumerate([&color](IFillStyle& style) {
		style.SetColor(color);
	});
}
