#pragma once
#include <vector>
#include <memory>

class Shape;

class PictureDraft
{
public:
	bool IsEmpty()const;
	void AddShape(std::unique_ptr<Shape> && shape);

private:
	std::vector<std::unique_ptr<Shape>> m_shapes;
};
