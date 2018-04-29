#pragma once
#include "CommonTypes.h"
#include "ICanvasDrawable.h"

class IFillStyle;
class IOutlineStyle;
class ICompositeShape;

class IShape : public ICanvasDrawable
{
public:
	virtual ~IShape() = default;

	virtual RectF GetFrame()const = 0;
	virtual void SetFrame(const RectF& frame) = 0;

	virtual IFillStyle& GetFillStyle() = 0;
	virtual const IFillStyle& GetFillStyle()const = 0;

	virtual IOutlineStyle& GetOutlineStyle() = 0;
	virtual const IOutlineStyle& GetOutlineStyle()const = 0;

	virtual ICompositeShape* GetComposite() = 0;
	virtual const ICompositeShape* GetComposite()const = 0;
};
