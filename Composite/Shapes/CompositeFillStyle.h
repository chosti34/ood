#pragma once
#include "IFillStyle.h"

class ICompositeShape;

class CompositeFillStyle : public IFillStyle
{
public:
	CompositeFillStyle(ICompositeShape& composite);

	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<uint32_t> GetColor()const override;
	void SetColor(uint32_t color) override;

private:
	ICompositeShape& m_composite;
};
