#include "stdafx.h"
#include "CompositeFillStyle.h"
#include "ICompositeShape.h"
#include "GetCompositePropertyValue.h"

CompositeFillStyle::CompositeFillStyle(IStyleEnumerator<IFillStyle>& enumerator)
	: m_enumerator(enumerator)
{
}

boost::optional<bool> CompositeFillStyle::IsEnabled()const
{
	boost::optional<bool> enabled;
	bool passed = false;
	m_enumerator.Enumerate([&](IFillStyle& style) {
		if (!passed)
		{
			enabled = style.IsEnabled();
			passed = true;
		}
		else if (enabled != style.IsEnabled())
		{
		}
	});
	return enabled;
}

void CompositeFillStyle::Enable(bool enable)
{
	m_enumerator.Enumerate([](IFillStyle& style) {
		style.Enable(true);
	});
}

boost::optional<uint32_t> CompositeFillStyle::GetColor()const
{
	m_enumerator.Enumerate([](IFillStyle& style) {

	});
}

void CompositeFillStyle::SetColor(uint32_t color)
{
	m_enumerator.Enumerate([&color](IFillStyle& style) {
		style.SetColor(color);
	});
}
