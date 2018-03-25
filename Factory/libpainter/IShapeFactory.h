#pragma once
#include <string>
#include <memory>

class Shape;

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;
	virtual std::unique_ptr<Shape> CreateShape(const std::string& description) = 0;
};
