#pragma once
#include "../libpainter/ICanvas.h"

class ConsoleCanvas : public ICanvas
{
public:
	virtual void SetColor(const Color& color) override;
	virtual void DrawLine(const Point& from, const Point& to) override;
	virtual void DrawEllipse(const Point& center, float horizontalRadius, float verticalRadius) override;
};
