#include "stdafx.h"
#include "ConsoleCanvas.h"

void ConsoleCanvas::SetColor(const Color& color)
{
	std::cout << "Color set to #" << color.ToString() << std::endl;
}

void ConsoleCanvas::DrawLine(const Point& from, const Point& to)
{
	std::cout << "Draw line from (" << from.x << ", " << from.y << ") " <<
		"to (" << to.x << ", " << to.y << ")" << std::endl;
}

void ConsoleCanvas::DrawEllipse(const Point& center, float horizontalRadius, float verticalRadius)
{
	std::cout << "Draw ellipse at (" << center.x << ", " << center.y << ") " <<
		"with a = " << horizontalRadius << ", b = " << verticalRadius << std::endl;
}
