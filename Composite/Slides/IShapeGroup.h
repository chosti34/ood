#pragma once
#include "IShape.h"
#include "IShapes.h"

class IShapeGroup : public IShape, public IShapes
{
public:
	virtual ~IShapeGroup() = default;
};
