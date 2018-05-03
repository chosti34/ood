#pragma once
#include "IFillStyle.h"

class LeafFillStyle : public IFillStyle
{
public:
	LeafFillStyle(bool enabled = true, uint32_t color = std::numeric_limits<uint32_t>::max());

	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<uint32_t> GetColor()const override;
	void SetColor(uint32_t color) override;

private:
	bool m_enabled;
	uint32_t m_color;
};
