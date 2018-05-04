#pragma once
#include "IOutlineStyle.h"

class ICompositeShape;

class CompositeOutlineStyle : public IOutlineStyle
{
public:
	CompositeOutlineStyle(ICompositeShape& composite);

	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<uint32_t> GetColor()const override;
	void SetColor(uint32_t color) override;

	boost::optional<float> GetThickness()const override;
	void SetThickness(float thickness) override;

private:
	ICompositeShape& m_composite;
};
