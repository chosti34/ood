#pragma once
#include "IShape.h"
#include <memory>

class LeafShape : public IShape
{
public:
	LeafShape();
	virtual ~LeafShape();

	void Draw(ICanvas& canvas)const override;

	// RectF GetFrame()const override;
	// void SetFrame(const RectF& frame) override;

	IFillStyle& GetFillStyle() override;
	const IFillStyle& GetFillStyle()const override;

	IOutlineStyle& GetOutlineStyle() override;
	const IOutlineStyle& GetOutlineStyle()const override;

	ICompositeShape* GetComposite() override;
	const ICompositeShape* GetComposite()const override;

protected:
	virtual void StrokeDrawImpl(ICanvas& canvas)const = 0;
	virtual void FillDrawImpl(ICanvas& canvas)const = 0;

private:
	std::unique_ptr<IFillStyle> m_fillStyle;
	std::unique_ptr<IOutlineStyle> m_outlineStyle;
};
