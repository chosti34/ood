#include "stdafx.h"
#include "ConsoleCanvas.h"

void ConsoleCanvas::SetColor(const Color& color)
{
	std::cout << "Color set to #" << ToString(color) << std::endl;
}

void ConsoleCanvas::DrawLine(const Point2D& from, const Point2D& to)
{
	std::cout << "Draw line from (" << from.x << ", " << from.y << ") " <<
		"to (" << to.x << ", " << to.y << ")" << std::endl;
}

void ConsoleCanvas::DrawEllipse(const Point2D& center, float horizontalRadius, float verticalRadius)
{
	std::cout << "Draw ellipse at (" << center.x << ", " << center.y << ") " <<
		"with a = " << horizontalRadius << ", b = " << verticalRadius << std::endl;
}
