#pragma once
#include <cstdint>

namespace graphics_lib
{
// ����� ��� ���������
class ICanvas
{
public:
	virtual ~ICanvas() = default;

	// ��������� ����� � ������� 0xRRGGBB
	virtual void SetColor(uint32_t color) = 0;
	// ������ "����" � ����� x, y
	virtual void MoveTo(int x, int y) = 0;
	// ������ ����� � ������� �������, ���������� ���� � ����� x,y 
	virtual void LineTo(int x, int y) = 0;
};
}
