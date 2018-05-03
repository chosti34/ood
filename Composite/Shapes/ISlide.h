#pragma once
#include "IShapeCollection.h"
#include "ICanvasDrawable.h"

class ISlide : public ICanvasDrawable
{
public:
	virtual ~ISlide() = default;

	virtual float GetWidth()const = 0;
	virtual float GetHeight()const = 0;

	virtual IShapeCollection& GetShapes() = 0;
};
