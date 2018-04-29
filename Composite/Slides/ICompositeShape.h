#pragma once
#include "IShape.h"
#include "IShapeCollection.h"

class ICompositeShape : public IShape, public IShapeCollection
{
public:
	virtual ~ICompositeShape() = default;
};
