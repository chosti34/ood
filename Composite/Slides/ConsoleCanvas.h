#pragma once
#include "ICanvas.h"
#include <ostream>

class ConsoleCanvas : public ICanvas
{
public:
	ConsoleCanvas(std::ostream& output);

	virtual void DrawLine(const Point2D & from, const Point2D & to) override;
	virtual void FillPolygon(const std::vector<Point2D>& points) override;

	virtual void DrawEllipse(const Point2D & center, float horizontalRadius, float verticalRadius) override;
	virtual void FillEllipse(const Point2D & center, float horizontalRadius, float verticalRadius) override;

	virtual void SetFillColor(uint32_t fillColor) override;
	virtual void SetOutlineColor(uint32_t outlineColor) override;
	virtual void SetOutlineThickness(unsigned thickness) override;

private:
	std::ostream& m_output;
	uint32_t m_fillColor;
	uint32_t m_outlineColor;
	unsigned m_outlineThickness;
};
