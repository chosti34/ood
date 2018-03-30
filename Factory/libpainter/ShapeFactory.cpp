#include "stdafx.h"
#include "ShapeFactory.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "RegularPolygon.h"

using namespace std;

namespace
{
const std::unordered_map<std::string, Color> REGULAR_COLORS_MAP = {
	{ "green", Color{ 0, 0xff, 0 } },
	{ "red", Color{ 0xff, 0, 0 } },
	{ "blue", Color{ 0, 0, 0xff } },
	{ "yellow", Color{ 0xff, 0xff, 0 } },
	{ "pink", Color{ 0xff, 0x69, 0xb4 } },
	{ "black", Color{ 0, 0, 0 } }
};

bool ParseColor(istream& strm, Color& color)
{
	string buffer;
	strm >> buffer;

	auto found = REGULAR_COLORS_MAP.find(buffer);
	if (found != REGULAR_COLORS_MAP.end())
	{
		color = found->second;
		return true;
	}

	if (buffer.length() == 6u)
	{
		Color copy = color;
		try
		{
			color.r = stoi(buffer.substr(0u, 2u), nullptr, 16);
			color.g = stoi(buffer.substr(2u, 2u), nullptr, 16);
			color.b = stoi(buffer.substr(4u, 2u), nullptr, 16);
			return true;
		}
		catch (...)
		{
			color = move(copy);
		}
	}
	return false;
}

unique_ptr<Rectangle> ParseAndCreateRectangle(istream& strm)
{
	Point2D leftTop;
	Point2D rightBottom;
	Color color;
	if (strm >> leftTop && strm >> rightBottom && ParseColor(strm, color))
	{
		return make_unique<Rectangle>(leftTop, rightBottom, color);
	}
	throw invalid_argument("bad rectangle arguments");
}
unique_ptr<Ellipse> ParseAndCreateEllipse(istream& strm)
{
	Point2D center;
	float horizontalRadius;
	float verticalRadius;
	Color color;
	if (strm >> center &&
		strm >> horizontalRadius &&
		strm >> verticalRadius &&
		ParseColor(strm, color))
	{
		return make_unique<Ellipse>(center, horizontalRadius, verticalRadius, color);
	}
	throw invalid_argument("bad ellipse arguments");
}
unique_ptr<Triangle> ParseAndCreateTriangle(istream& strm)
{
	Point2D p1;
	Point2D p2;
	Point2D p3;
	Color color;
	if (strm >> p1.x &&
		strm >> p1.y &&
		strm >> p2.x &&
		strm >> p2.y &&
		strm >> p3.x &&
		strm >> p3.y &&
		ParseColor(strm, color))
	{
		return std::make_unique<Triangle>(p1, p2, p3, color);
	}
	throw invalid_argument("bad triangle arguments");
}
unique_ptr<RegularPolygon> ParseAndCreateRegularPolygon(istream& strm)
{
	Point2D center;
	float radius;
	unsigned vertexCount;
	Color color;
	if (strm >> center &&
		strm >> radius &&
		strm >> vertexCount &&
		ParseColor(strm, color))
	{
		return make_unique<RegularPolygon>(center, radius, vertexCount, color);
	}
	throw invalid_argument("bad regular polygon arguments");
}

const unordered_map<string, function<unique_ptr<Shape>(istream& strm)>> DISPATCH_MAP = {
	{ "Rectangle", ParseAndCreateRectangle },
	{ "Ellipse", ParseAndCreateEllipse },
	{ "Triangle", ParseAndCreateTriangle },
	{ "RegularPolygon", ParseAndCreateRegularPolygon }
};
}

unique_ptr<Shape> ShapeFactory::CreateShape(const string& description)
{
	istringstream strm(description);
	string shapeName;
	strm >> shapeName;
	auto found = DISPATCH_MAP.find(shapeName);
	if (found != DISPATCH_MAP.end())
	{
		auto& fn = found->second;
		return fn(strm);
	}
	throw invalid_argument("unknown shape name");
}
