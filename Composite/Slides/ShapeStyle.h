#pragma once
#include "IShapeStyle.h"

class ShapeStyle : public IShapeStyle
{
public:
	ShapeStyle(bool enabled = true, uint32_t color = 0, unsigned thickness = 1);

	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<uint32_t> GetColor()const override;
	void SetColor(boost::optional<uint32_t> color) override;

	boost::optional<unsigned> GetThickness()const override;
	void SetThickness(boost::optional<unsigned> thickness) override;

private:
	bool m_enabled;
	boost::optional<uint32_t> m_color;
	boost::optional<unsigned> m_thickness;
};
