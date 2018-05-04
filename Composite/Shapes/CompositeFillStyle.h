#pragma once
#include "IFillStyle.h"
#include "IStyleEnumerator.h"

class CompositeFillStyle : public IFillStyle
{
public:
	CompositeFillStyle(IStyleEnumerator<IFillStyle>& enumerator);

	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<uint32_t> GetColor()const override;
	void SetColor(uint32_t color) override;

private:
	IStyleEnumerator<IFillStyle>& m_enumerator;
};
