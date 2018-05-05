#pragma once
#include "IFillStyle.h"
#include "StyleEnumerator.h"

class CompositeFillStyle : public IFillStyle
{
public:
	CompositeFillStyle(StyleEnumerator<IFillStyle> && enumerate);

	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<uint32_t> GetColor()const override;
	void SetColor(uint32_t color) override;

private:
	StyleEnumerator<IFillStyle> m_enumerate;
};
