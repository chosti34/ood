#pragma once
#include "IShape.h"
#include "IShapeCollection.h"
#include <functional>

class ICompositeShape : public IShape, public IShapeCollection
{
public:
	virtual ~ICompositeShape() = default;
};
