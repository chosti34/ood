#pragma once
#include "IShapeComposite.h"
#include "ShapeCollection.h"

class ShapeComposite : public IShapeComposite
{
public:
	ShapeComposite();

	/* Ìועמהû טםעונפויסא IShape */
	void Draw(ICanvas& canvas)const override;

	RectF GetFrame()const override;
	void SetFrame(const RectF& frame) override;

	IShapeStyle& GetFillStyle() override;
	const IShapeStyle& GetFillStyle()const override;

	IShapeStyle& GetOutlineStyle() override;
	const IShapeStyle& GetOutlineStyle()const override;

	IShapeComposite* GetComposite() override;
	const IShapeComposite* GetComposite()const override;

	/* Ìועמהû טםעונפויסא IShapeCollection */
	void InsertShape(
		const std::shared_ptr<IShape>& shape,
		size_t index = std::numeric_limits<size_t>::max()) override;
	void RemoveShape(size_t index) override;

	std::shared_ptr<IShape> GetShape(size_t index) override;
	std::shared_ptr<const IShape> GetShape(size_t index)const override;

	size_t GetShapesCount()const override;

private:
	std::unique_ptr<IShapeStyle> m_fillStyle;
	std::unique_ptr<IShapeStyle> m_outlineStyle;
	ShapeCollection m_shapes;
};
