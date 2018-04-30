#include "stdafx.h"
#include "ShapeCollection.h"
#include "CompositeShape.h"
#include "Slide.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "ConsoleCanvas.h"
#include "IOutlineStyle.h"
#include "IFillStyle.h"

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	Slide slide(100, 100);
	/*auto rectangle = std::make_shared<Rectangle>(Point2D{ 0, 0 }, 10.f, 10.f);
	auto triangle = std::make_shared<Triangle>(Point2D{ 1, 1 }, Point2D{ 2, 3 }, Point2D{ 4, 0 });
	auto ellipse = std::make_shared<Ellipse>(Point2D{ 100, 100 }, 50.f, 50.f);

	auto composite = std::make_shared<CompositeShape>();
	composite->InsertShape(rectangle);
	composite->InsertShape(triangle);
	composite->InsertShape(ellipse);

	auto inner = std::make_shared<CompositeShape>();
	inner->InsertShape(std::make_shared<Rectangle>(Point2D{ 100.f, 100.f }, 300.f, 100.f));
	composite->InsertShape(inner);

	auto& style = composite->GetOutlineStyle();
	style.SetThickness(2);
	style.Enable(false);

	composite->GetFillStyle().Enable(true);
	composite->GetFillStyle().SetColor(123);*/

	auto triangle = std::make_shared<Triangle>(Point2D{ 100, 100 }, Point2D{ 150, 50 }, Point2D{ 200, 100 });
	triangle->SetFrame(RectF{ 100, 50, 50, 50 });

	ConsoleCanvas canvas(std::cout);

	slide.GetShapes().InsertShape(triangle);
	slide.Draw(canvas);
	return 0;
}
