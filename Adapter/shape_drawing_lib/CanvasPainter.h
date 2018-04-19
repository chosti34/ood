#pragma once
#include "ICanvasDrawable.h"
#include "../graphics_lib/ICanvas.h"

namespace shape_drawing_lib
{
// ��������, ��������� �������� ICanvasDrawable-������� �� ICanvas
class CCanvasPainter
{
public:
	CCanvasPainter(graphics_lib::ICanvas& canvas);
	void Draw(const ICanvasDrawable& drawable);

private:
	graphics_lib::ICanvas& m_canvas;
};
}
