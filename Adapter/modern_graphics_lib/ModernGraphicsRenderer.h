#pragma once
#include "Point.h"
#include "Color.h"
#include <iosfwd>

namespace modern_graphics_lib
{
// Класс для современного рисования графики
class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(std::ostream& strm);
	~CModernGraphicsRenderer();

	// Этот метод должен быть вызван в начале рисования
	void BeginDraw();

	// Выполняет рисование линии
	void DrawLine(const CPoint& start, const CPoint& end, const Color& color);

	// Этот метод должен быть вызван в конце рисования
	void EndDraw();

private:
	std::ostream& m_out;
	bool m_drawing;
};
}
