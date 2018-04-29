#pragma once
#include "IShape.h"

class Shape : public IShape
{
public:
	Shape();

	void Draw(ICanvas& canvas)const override;

	RectF GetFrame()const override;
	void SetFrame(const RectF& frame) override;

	IShapeStyle& GetFillStyle() override;
	const IShapeStyle& GetFillStyle()const override;

	IShapeStyle& GetOutlineStyle() override;
	const IShapeStyle& GetOutlineStyle()const override;

	IShapeComposite* GetComposite() override;
	const IShapeComposite* GetComposite()const override;

protected:
	virtual void StrokeDrawImpl(ICanvas& canvas)const = 0;
	virtual void FillDrawImpl(ICanvas& canvas)const = 0;

private:
	std::unique_ptr<IShapeStyle> m_fillStyle;
	std::unique_ptr<IShapeStyle> m_outlineStyle;
};
