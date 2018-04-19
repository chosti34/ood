#include "stdafx.h"
#include "ModernGraphicsRenderer.h"

using namespace std;
using namespace modern_graphics_lib;

CModernGraphicsRenderer::CModernGraphicsRenderer(std::ostream& strm)
	: m_out(strm)
	, m_drawing(false)
{
}

CModernGraphicsRenderer::~CModernGraphicsRenderer()
{
	if (m_drawing) // «авершаем рисование, если оно было начато
	{
		EndDraw();
	}
}

void CModernGraphicsRenderer::BeginDraw()
{
	if (m_drawing)
	{
		throw logic_error("Drawing has already begun");
	}
	m_out << "<draw>" << endl;
	m_drawing = true;
}

void CModernGraphicsRenderer::DrawLine(const CPoint& start, const CPoint& end, const Color& color)
{
	if (!m_drawing)
	{
		throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
	}
	m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%" />)")
		% start.x % start.y % end.x % end.y << endl;
	m_out << boost::format(R"(    <color r="%1%" g="%2%" b="%3%" a="%4%" />)")
		% color.r % color.g % color.b % color.a << endl;
	m_out << "  </line>" << endl;
}

void CModernGraphicsRenderer::EndDraw()
{
	if (!m_drawing)
	{
		throw logic_error("Drawing has not been started");
	}
	m_out << "</draw>" << endl;
	m_drawing = false;
}
