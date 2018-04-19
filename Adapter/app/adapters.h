#pragma once
#include "../graphics_lib/ICanvas.h"
#include "../modern_graphics_lib/ModernGraphicsRenderer.h"

// Адаптер объекта
class ModernGraphicsRendererObjectAdapter : public graphics_lib::ICanvas
{
public:
	ModernGraphicsRendererObjectAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
		: m_renderer(renderer)
		, m_penPosition(0, 0)
		, m_color(0, 0, 0, 1.f)
	{
		m_renderer.BeginDraw();
	}

	void SetColor(uint32_t color) override
	{
		m_color = modern_graphics_lib::ToRGBA(color);
	}

	void MoveTo(int x, int y) override
	{
		m_penPosition.x = x;
		m_penPosition.y = y;
	}

	void LineTo(int x, int y) override
	{
		m_renderer.DrawLine(m_penPosition, modern_graphics_lib::CPoint(x, y), m_color);
		MoveTo(x, y);
	}

private:
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
	modern_graphics_lib::CPoint m_penPosition;
	modern_graphics_lib::Color m_color;
};

// Адаптер класса
class ModernGraphicsRendererClassAdapter
	: public graphics_lib::ICanvas
	, private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	ModernGraphicsRendererClassAdapter(std::ostream& strm)
		: modern_graphics_lib::CModernGraphicsRenderer(strm)
		, m_penPosition(0, 0)
		, m_color(0, 0, 0, 1.f)
	{
		BeginDraw();
	}

	void SetColor(uint32_t color) override
	{
		m_color = modern_graphics_lib::ToRGBA(color);
	}

	void MoveTo(int x, int y) override
	{
		m_penPosition.x = x;
		m_penPosition.y = y;
	}

	void LineTo(int x, int y) override
	{
		DrawLine(m_penPosition, modern_graphics_lib::CPoint(x, y), m_color);
		MoveTo(x, y);
	}

private:
	modern_graphics_lib::CPoint m_penPosition;
	modern_graphics_lib::Color m_color;
};
