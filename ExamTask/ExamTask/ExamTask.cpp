// ExamTask.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

struct Point
{
	float x;
	float y;
};

class Rectangle;
class Triangle;
class Circle;

class IShapeVisitor
{
public:
	virtual void Visit(const Rectangle& rectangle) = 0;
	virtual void Visit(const Triangle& triangle) = 0;
	virtual void Visit(const Circle& circle) = 0;

protected:
	~IShapeVisitor() = default;
};

class IShape
{
public:
	virtual ~IShape() = default;
	virtual void Accept(IShapeVisitor& visitor)const = 0;
};

class Rectangle : public IShape
{
public:
	Rectangle(const Point& leftTop, float width, float height)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
	{
	}

	void Accept(IShapeVisitor& visitor)const override
	{
		visitor.Visit(*this);
	}

	const Point& GetLeftTop()const
	{
		return m_leftTop;
	}

	float GetWidth()const
	{
		return m_width;
	}

	float GetHeight()const
	{
		return m_height;
	}

private:
	Point m_leftTop;
	float m_width;
	float m_height;
};

class Triangle : public IShape
{
public:
	Triangle(const Point& p1, const Point& p2, const Point& p3)
		: m_p1(p1)
		, m_p2(p2)
		, m_p3(p3)
	{
	}

	void Accept(IShapeVisitor& visitor)const override
	{
		visitor.Visit(*this);
	}

	const Point& GetVertex1()const
	{
		return m_p1;
	}

	const Point& GetVertex2()const
	{
		return m_p2;
	}

	const Point& GetVertex3()const
	{
		return m_p3;
	}

private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
};

class Circle : public IShape
{
public:
	Circle(const Point& center, float radius)
		: m_center(center)
		, m_radius(radius)
	{
	}

	void Accept(IShapeVisitor& visitor)const override
	{
		visitor.Visit(*this);
	}

	const Point& GetCenter()const
	{
		return m_center;
	}

	float GetRadius()const
	{
		return m_radius;
	}

private:
	Point m_center;
	float m_radius;
};

class ShapeAreaCalculator : public IShapeVisitor
{
public:
	float GetShapeArea(const IShape& shape)
	{
		shape.Accept(*this);
		return m_calculated;
	}

	void Visit(const Rectangle& rectangle) override
	{
		m_calculated = rectangle.GetHeight() * rectangle.GetWidth();
	}

	void Visit(const Triangle& triangle) override
	{
		const Point& p1 = triangle.GetVertex1();
		const Point& p2 = triangle.GetVertex2();
		const Point& p3 = triangle.GetVertex3();
		m_calculated = 0.5f * std::abs((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y));
	}

	void Visit(const Circle& circle) override
	{
		m_calculated = 3.14f * circle.GetRadius() * circle.GetRadius();
	}

private:
	float m_calculated = 0.f;
};

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void DrawLine(const Point& from, const Point& to) = 0;
	virtual void DrawEllipse(const Point& center, float radius) = 0;
};

class Canvas : public ICanvas
{
public:
	void DrawLine(const Point& from, const Point& to) override
	{
		std::cout << "<DrawLine fromX=" << from.x << " fromY=" << from.y
			<< " toX=" << to.x << " toY=" << to.y << ">\n";
	}

	void DrawEllipse(const Point& center, float radius) override
	{
		std::cout << "<DrawEllipse centerX=" << center.x << " centerY=" << center.y
			<< " radius=" << radius << ">\n";
	}
};

class ShapeDrawer : public IShapeVisitor
{
public:
	ShapeDrawer(std::unique_ptr<ICanvas> && canvas)
		: m_canvas(std::move(canvas))
	{
	}

	void Visit(const Rectangle& rectangle)override
	{
		const Point& leftTop = rectangle.GetLeftTop();
		m_canvas->DrawLine(leftTop, { leftTop.x + rectangle.GetWidth() });
		m_canvas->DrawLine(
			{ leftTop.x + rectangle.GetWidth(), leftTop.y },
			{ leftTop.x + rectangle.GetWidth(), leftTop.y + rectangle.GetHeight() });
		m_canvas->DrawLine(
			{ leftTop.x + rectangle.GetWidth(), leftTop.y + rectangle.GetHeight() },
			{ leftTop.x, leftTop.y + rectangle.GetHeight() });
		m_canvas->DrawLine({ leftTop.x, leftTop.y + rectangle.GetHeight() }, leftTop);
	}

	void Visit(const Triangle& triangle)override
	{
		m_canvas->DrawLine(triangle.GetVertex1(), triangle.GetVertex2());
		m_canvas->DrawLine(triangle.GetVertex2(), triangle.GetVertex3());
		m_canvas->DrawLine(triangle.GetVertex3(), triangle.GetVertex1());
	}

	void Visit(const Circle& circle)override
	{
		m_canvas->DrawEllipse(circle.GetCenter(), circle.GetRadius());
	}

private:
	std::unique_ptr<ICanvas> m_canvas;
};

int main()
{
	float totalArea = 0.f;

	auto drawer = std::make_unique<ShapeDrawer>(std::make_unique<Canvas>());
	auto calculator = std::make_unique<ShapeAreaCalculator>();

	std::vector<std::shared_ptr<IShape>> shapes = {
		std::make_shared<Rectangle>(Point{ 0, 0 }, 10.f, 10.f),
		std::make_shared<Triangle>(Point{ 2, -3 }, Point{ 1, 1 }, Point{ -6, 5 }),
		std::make_shared<Circle>(Point{ 10, 10 }, 10.f),
	};

	std::for_each(shapes.begin(), shapes.end(), [&](const auto& shape) {
		const float area = calculator->GetShapeArea(*shape);
		totalArea += area;
		std::cout << "Area = " << area << std::endl;
		shape->Accept(*drawer);
	});

	std::cout << "Total area = " << totalArea << std::endl;
	return 0;
}
