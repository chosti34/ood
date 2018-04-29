#pragma once
#include "IShape.h"
#include "IShapeCollection.h"

class IShapeComposite : public IShape, public IShapeCollection
{
public:
	virtual ~IShapeComposite() = default;
};
