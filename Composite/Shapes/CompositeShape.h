#pragma once
#include "ICompositeShape.h"
#include "ShapeCollection.h"

class CompositeShape : public ICompositeShape
{
public:
	CompositeShape();

	/* Ìועמהû טםעונפויסא IShape */
	void Draw(ICanvas& canvas)const override;

	RectF GetFrame()const override;
	void SetFrame(const RectF& frame) override;

	IFillStyle& GetFillStyle() override;
	const IFillStyle& GetFillStyle()const override;

	IOutlineStyle& GetOutlineStyle() override;
	const IOutlineStyle& GetOutlineStyle()const override;

	ICompositeShape* GetComposite() override;
	const ICompositeShape* GetComposite()const override;

	/* Ìועמהû טםעונפויסא IShapeCollection */
	void InsertShape(
		const std::shared_ptr<IShape>& shape,
		size_t index = std::numeric_limits<size_t>::max()) override;
	void RemoveShape(size_t index) override;

	std::shared_ptr<IShape> GetShape(size_t index) override;
	std::shared_ptr<const IShape> GetShape(size_t index)const override;

	size_t GetShapesCount()const override;

private:
	std::unique_ptr<IFillStyle> m_fillStyle;
	std::unique_ptr<IOutlineStyle> m_outlineStyle;
	ShapeCollection m_shapes;
};
