#pragma once
#include "IOutlineStyle.h"

class LeafOutlineStyle : public IOutlineStyle
{
public:
	LeafOutlineStyle(bool enabled = true, uint32_t color = 0, unsigned thickness = 1);

	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<uint32_t> GetColor()const override;
	void SetColor(uint32_t color) override;

	boost::optional<unsigned> GetThickness()const override;
	void SetThickness(unsigned thickness) override;

private:
	bool m_enabled;
	uint32_t m_color;
	unsigned m_thickness;
};
