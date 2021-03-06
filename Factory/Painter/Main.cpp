#include "stdafx.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/Designer.h"
#include "../libpainter/Painter.h"
#include "ConsoleCanvas.h"
#include "D2DCanvas.h"
#include "Window.h"

namespace
{
void OpenWindowAndDrawShapes(const PictureDraft& draft)
{
	auto window = std::make_unique<Window>();
	auto painter = std::make_unique<Painter>();
	auto canvas = std::make_unique<D2DCanvas>(window->GetHandle());

	while (window->IsOpen())
	{
		if (!window->PeekAndProcessEvent())
		{
			canvas->BeginDraw();
			canvas->Clear(Color{ 255u, 255u, 255u });
			painter->DrawPicture(draft, *canvas);
			canvas->EndDraw();
		}
	}
}

void PrintUsageInstructions(std::ostream& strm)
{
	strm << "Usage: Painter.exe <shapes file path>" << std::endl;
	strm << "Every shape must be delimited by newline character" << std::endl;
	strm << "List of available shapes: (every point is two numbers)" << std::endl;
	strm << "Triangle <point1> <point2> <point3> <color>" << std::endl;
	strm << "Rectangle <left top point> <right bottom point> <color>" << std::endl;
	strm << "Ellipse <center point> <horizontal radius> <vertical radius> <color>" << std::endl;
	strm << "RegularPolygon <center point> <radius> <vertex count> <color>" << std::endl;
	strm << "Colors can be written in hex format like 'ff00ff'" << std::endl;
	strm << "If wanted color is in above list, it can be written by word" << std::endl;
	strm << "[green, red, blue, yellow, pink, black]" << std::endl;
}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Invalid arguments count!" << std::endl;
		PrintUsageInstructions(std::cerr);
		return 1;
	}

	try
	{
		auto factory = std::make_unique<ShapeFactory>();
		auto designer = std::make_unique<Designer>(*factory);

		std::ifstream file(argv[1]);
		auto draft = designer->CreateDraft(file);

		OpenWindowAndDrawShapes(draft);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
