#include "stdafx.h"
#include "ConsoleCanvas.h"
#include <boost/format.hpp>

ConsoleCanvas::ConsoleCanvas(std::ostream& output)
	: m_fillColor(0)
	, m_outlineColor(0)
	, m_outlineThickness(1)
	, m_output(output)
{
}

void ConsoleCanvas::DrawLine(const Point2D& from, const Point2D& to)
{
	m_output << boost::format(R"(<DrawLine fromX="%1%" fromY="%2%" toX="%3%" toY="%4%" />)")
		% from.x % from.y % to.x % to.y << "\n";
}

void ConsoleCanvas::FillPolygon(const std::vector<Point2D>& points)
{
	m_output << "<FillPolygon>\n";
	for (const auto& point : points)
	{
		m_output << boost::format(R"(<Point x="%1%" y="%2%" />)") % point.x % point.y << "\n";
	}
	m_output << "</FillPolygon>\n";
}

void ConsoleCanvas::DrawEllipse(const Point2D& center, float horizontalRadius, float verticalRadius)
{
	m_output << boost::format(R"(<DrawEllipse centerX="%1%" centerY="%2%" a="%3%" b="%4%" />)")
		% center.x % center.y % horizontalRadius % verticalRadius << "\n";
}

void ConsoleCanvas::FillEllipse(const Point2D& center, float horizontalRadius, float verticalRadius)
{
	m_output << boost::format(R"(<FillEllipse centerX="%1%" centerY="%2%" a="%3%" b="%4%" />)")
		% center.x % center.y % horizontalRadius % verticalRadius << "\n";
}

void ConsoleCanvas::SetFillColor(uint32_t fillColor)
{
	m_output << "<SetFillColor value=\"" << fillColor << "\" />\n";
}

void ConsoleCanvas::SetOutlineColor(uint32_t outlineColor)
{
	m_output << "<SetOutlineColor value=\"" << outlineColor << "\" />\n";
}

void ConsoleCanvas::SetOutlineThickness(unsigned thickness)
{
	m_output << "<SetOutlineThickness value=\"" << thickness << "\" />\n";
}
