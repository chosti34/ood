#include "stdafx.h"
#include "../graphics_lib/Canvas.h"
#include "../shape_drawing_lib/CanvasPainter.h"
#include "../shape_drawing_lib/ICanvasDrawable.h"
#include "../shape_drawing_lib/Point.h"
#include "../shape_drawing_lib/Triangle.h"
#include "../shape_drawing_lib/Rectangle.h"
#include "../modern_graphics_lib/ModernGraphicsRenderer.h"
#include "adapters.h"

using namespace std;

namespace app
{
void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0xFFFF);
	CRectangle rectangle({ 30, 40 }, 18, 24, 0xFF);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	// Адаптер объекта поддерживает композицию и агрегацию
	// modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
	// ModernGraphicsRendererObjectAdapter objectAdapter(renderer);

	// Адаптер класса не позволяет агрегировать адаптируемый объект
	ModernGraphicsRendererClassAdapter classAdapter(cout);

	shape_drawing_lib::CCanvasPainter painter(classAdapter);
	PaintPicture(painter);
}
}

int main()
{
	cout << "Should we use new API (y)?";
	string userInput;
	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}
	return 0;
}
