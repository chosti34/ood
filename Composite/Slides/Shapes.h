#pragma once
#include "IShapes.h"

class Shapes : public IShapes
{
public:
	void InsertShape(
		const std::shared_ptr<IShape>& shape,
		size_t index = std::numeric_limits<size_t>::max()) override;
	void RemoveShape(size_t index) override;

	std::shared_ptr<IShape> GetShape(size_t index) override;
	std::shared_ptr<const IShape> GetShape(size_t index)const override;

	size_t GetShapesCount()const override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};
