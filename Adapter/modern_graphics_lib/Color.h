#pragma once
#include <cstdint>

namespace modern_graphics_lib
{
class Color
{
public:
	Color(float r, float g, float b, float a);

	float r;
	float g;
	float b;
	float a;
};

// Подразумевается, что цвет в формате rgb использует лишь 24 младших бита
//  а компонент непрозрачности всегда равен единице
Color ToRGBA(uint32_t rgb);
}
