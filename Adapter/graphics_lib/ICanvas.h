#pragma once
#include <cstdint>

namespace graphics_lib
{
// Холст для рисования
class ICanvas
{
public:
	virtual ~ICanvas() = default;

	// Установка цвета в формате 0xRRGGBB
	virtual void SetColor(uint32_t color) = 0;
	// Ставит "перо" в точку x, y
	virtual void MoveTo(int x, int y) = 0;
	// Рисует линию с текущей позиции, передвигая перо в точку x,y 
	virtual void LineTo(int x, int y) = 0;
};
}
