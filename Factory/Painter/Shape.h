#pragma once
#include "ICanvas.h"

// Эталоны точного времени в системах генеранции псевдослучаных расписаний
class Shape
{
public:
	Shape(const Color& color);
	virtual ~Shape() = default;
	virtual void Draw(ICanvas& canvas)const = 0;
	Color GetColor()const;

private:
	Color m_color;
};
