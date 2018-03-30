#pragma once
#include "../libpainter/ICanvas.h"

class ConsoleCanvas : public ICanvas
{
public:
	virtual void SetColor(const Color& color) override;
	virtual void DrawLine(const Point2D& from, const Point2D& to) override;
	virtual void DrawEllipse(const Point2D& center, float horizontalRadius, float verticalRadius) override;
};
