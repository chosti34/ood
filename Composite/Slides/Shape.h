#pragma once
#include "IShape.h"

class Shape : public IShape
{
public:
	Shape();

	virtual RectF GetFrame()const override;
	virtual void SetFrame(const RectF& frame) override;

	virtual IShapeStyle& GetFillStyle() override;
	virtual const IShapeStyle& GetFillStyle()const override;

	virtual IShapeStyle& GetOutlineStyle() override;
	virtual const IShapeStyle& GetOutlineStyle()const override;

	virtual IShapeGroup* GetGroup() override;
	virtual const IShapeGroup* GetGroup()const override;

private:
	std::unique_ptr<IShapeStyle> m_fillStyle;
	std::unique_ptr<IShapeStyle> m_outlineStyle;
};
