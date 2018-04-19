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

// ���������������, ��� ���� � ������� rgb ���������� ���� 24 ������� ����
//  � ��������� �������������� ������ ����� �������
Color ToRGBA(uint32_t rgb);
}
