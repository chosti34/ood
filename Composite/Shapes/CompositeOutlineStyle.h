#pragma once
#include "IOutlineStyle.h"
#include "StyleEnumerator.h"

class CompositeOutlineStyle : public IOutlineStyle
{
public:
	CompositeOutlineStyle(StyleEnumerator<IOutlineStyle>&& enumerate);

	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<uint32_t> GetColor()const override;
	void SetColor(uint32_t color) override;

	boost::optional<float> GetThickness()const override;
	void SetThickness(float thickness) override;

private:
	StyleEnumerator<IOutlineStyle> m_enumerate;
};
