#pragma once
#include "IShapeGroup.h"
#include <vector>

class ShapeGroup : public IShapeGroup
{
public:
	ShapeGroup();

	void Draw(ICanvas& canvas)const override;

	RectF GetFrame()const override;
	void SetFrame(const RectF & frame) override;

	IShapeStyle& GetFillStyle() override;
	const IShapeStyle& GetFillStyle()const override;

	IShapeStyle& GetOutlineStyle() override;
	const IShapeStyle& GetOutlineStyle()const override;

	IShapeGroup* GetGroup() override;
	const IShapeGroup* GetGroup()const override;

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
	std::vector<std::shared_ptr<IShape>> m_shapes;
};
