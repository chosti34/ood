#pragma once
#include "../graphics_lib/ICanvas.h"

namespace shape_drawing_lib
{
// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas& canvas)const = 0;
	virtual ~ICanvasDrawable() = default;
};
}
