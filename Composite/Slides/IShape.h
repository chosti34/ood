#pragma once
#include "ICanvasDrawable.h"
#include "CommonTypes.h"
#include "IShapeStyle.h"
#include <memory>

class IShapeGroup;

class IShape : public ICanvasDrawable
{
public:
	virtual ~IShape() = default;

	virtual RectF GetFrame()const = 0;
	virtual void SetFrame(const RectF& frame) = 0;

	virtual const IShapeStyle& GetFillStyle()const = 0;
	virtual IShapeStyle& GetFillStyle() = 0;

	virtual const IShapeStyle& GetOutlineStyle()const = 0;
	virtual IShapeStyle& GetOutlineStyle() = 0;

	virtual IShapeGroup* GetGroup() = 0;
	virtual const IShapeGroup* GetGroup()const = 0;
};
