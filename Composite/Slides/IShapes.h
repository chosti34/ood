#pragma once
#include <memory>

class IShape;

class IShapes
{
public:
	virtual ~IShapes() = default;

	virtual void InsertShape(
		const std::shared_ptr<IShape>& shape,
		size_t index = std::numeric_limits<size_t>::max()) = 0;
	virtual void RemoveShape(size_t index) = 0;

	virtual std::shared_ptr<IShape> GetShape(size_t index) = 0;
	virtual std::shared_ptr<const IShape> GetShape(size_t index)const = 0;

	virtual size_t GetShapesCount()const = 0;
};
