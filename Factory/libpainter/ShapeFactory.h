#pragma once
#include "IShapeFactory.h"

class ShapeFactory : public IShapeFactory
{
public:
	std::unique_ptr<Shape> CreateShape(const std::string& description) override;
};
