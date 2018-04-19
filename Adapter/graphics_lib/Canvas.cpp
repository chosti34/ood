#include "stdafx.h"
#include "Canvas.h"

using namespace std;
using namespace graphics_lib;

void graphics_lib::CCanvas::SetColor(uint32_t color)
{
	cout << "SetColor (#" << setfill('0') << setw(6u) << hex << uppercase << color << ")" << dec << endl;
}

void CCanvas::MoveTo(int x, int y)
{
	cout << "MoveTo (" << x << ", " << y << ")" << endl;
}

void CCanvas::LineTo(int x, int y)
{
	cout << "LineTo (" << x << ", " << y << ")" << endl;
}
