#pragma once
#include "ICanvasDrawable.h"

class IShapeCollection;

class ISlide : public ICanvasDrawable
{
public:
	virtual ~ISlide() = default;

	virtual float GetWidth()const = 0;
	virtual float GetHeight()const = 0;

	virtual IShapeCollection& GetShapes() = 0;
	virtual const IShapeCollection& GetShapes()const = 0;
};
