#include "stdafx.h"
#include "CompositeOutlineStyle.h"

CompositeOutlineStyle::CompositeOutlineStyle(StyleEnumerator<IOutlineStyle> && enumerate)
	: m_enumerate(enumerate)
{
}

boost::optional<bool> CompositeOutlineStyle::IsEnabled()const
{
	return GetValueIfAllSame<IOutlineStyle, bool>(m_enumerate, [](const IOutlineStyle& style) {
		return style.IsEnabled();
	});
}

void CompositeOutlineStyle::Enable(bool enable)
{
	m_enumerate([&enable](IOutlineStyle& style) {
		style.Enable(enable);
	});
}

boost::optional<uint32_t> CompositeOutlineStyle::GetColor()const
{
	return GetValueIfAllSame<IOutlineStyle, uint32_t>(m_enumerate, [](const IOutlineStyle& style) {
		return style.GetColor();
	});
}

void CompositeOutlineStyle::SetColor(uint32_t color)
{
	m_enumerate([&color](IOutlineStyle& style) {
		style.SetColor(color);
	});
}

boost::optional<float> CompositeOutlineStyle::GetThickness()const
{
	return GetValueIfAllSame<IOutlineStyle, float>(m_enumerate, [](const IOutlineStyle& style) {
		return style.GetThickness();
	});
}

void CompositeOutlineStyle::SetThickness(float thickness)
{
	m_enumerate([&thickness](IOutlineStyle& style) {
		style.SetThickness(thickness);
	});
}
