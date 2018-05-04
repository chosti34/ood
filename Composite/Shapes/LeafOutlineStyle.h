#pragma once
#include "IOutlineStyle.h"

class LeafOutlineStyle : public IOutlineStyle
{
public:
	LeafOutlineStyle(bool enabled = true,
		uint32_t color = std::numeric_limits<uint32_t>::max(),
		float thickness = 1.f);

	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<uint32_t> GetColor()const override;
	void SetColor(uint32_t color) override;

	boost::optional<float> GetThickness()const override;
	void SetThickness(float thickness) override;

private:
	bool m_enabled;
	uint32_t m_color;
	float m_thickness;
};
