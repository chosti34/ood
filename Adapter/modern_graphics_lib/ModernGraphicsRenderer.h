#pragma once
#include "Point.h"
#include "Color.h"
#include <iosfwd>

namespace modern_graphics_lib
{
// ����� ��� ������������ ��������� �������
class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(std::ostream& strm);
	~CModernGraphicsRenderer();

	// ���� ����� ������ ���� ������ � ������ ���������
	void BeginDraw();

	// ��������� ��������� �����
	void DrawLine(const CPoint& start, const CPoint& end, const Color& color);

	// ���� ����� ������ ���� ������ � ����� ���������
	void EndDraw();

private:
	std::ostream& m_out;
	bool m_drawing;
};
}
