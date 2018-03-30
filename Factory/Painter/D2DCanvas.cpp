#include "stdafx.h"
#include "D2DCanvas.h"

namespace
{
constexpr float STROKE_WIDTH = 1.7f;

// Структура Color хранит компоненты цвета в диапазоне [0 .. 255],
//  но Direct2D ожидает их в формате [0 .. 1]
D2D1::ColorF GetNormalizedColor(const Color& color)
{
	D2D1::ColorF normalized(color.r, color.g, color.b);
	if (normalized.r >= 1.f)
	{
		normalized.r = std::fmodf(normalized.r, 256.f) / 255.f;
	}
	if (normalized.g >= 1.f)
	{
		normalized.g = std::fmodf(normalized.g, 256.f) / 255.f;
	}
	if (normalized.b >= 1.f)
	{
		normalized.b = std::fmodf(normalized.b, 256.f) / 255.f;
	}
	return normalized;
}
}

D2DCanvas::D2DCanvas(HWND hWnd)
	: m_renderTarget(nullptr)
	, m_factory(nullptr)
	, m_brush(nullptr)
{
	auto hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);
	assert(hr == S_OK);

	RECT rect;
	auto r = GetClientRect(hWnd, &rect);
	assert(r == TRUE);

	hr = m_factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rect.right, rect.bottom)),
		&m_renderTarget
	);
	assert(hr == S_OK);

	hr = m_renderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Silver), &m_brush); // Цвет в любом случае будет изменён
	assert(hr == S_OK);
}

D2DCanvas::~D2DCanvas()
{
	if (m_factory)
	{
		m_factory->Release();
	}
	if (m_renderTarget)
	{
		m_renderTarget->Release();
	}
	if (m_brush)
	{
		m_brush->Release();
	}
}

void D2DCanvas::BeginDraw()
{
	m_renderTarget->BeginDraw();
}

void D2DCanvas::EndDraw()
{
	m_renderTarget->EndDraw();
}

void D2DCanvas::Clear(const Color& color)
{
	m_renderTarget->Clear(GetNormalizedColor(color));
}

void D2DCanvas::SetColor(const Color& color)
{
	m_brush->SetColor(GetNormalizedColor(color));
}

void D2DCanvas::DrawLine(const Point2D& from, const Point2D& to)
{
	m_renderTarget->DrawLine(
		D2D1::Point2F(from.x, from.y),
		D2D1::Point2F(to.x, to.y),
		m_brush, STROKE_WIDTH);
}

void D2DCanvas::DrawEllipse(const Point2D& center, float horizontalRadius, float verticalRadius)
{
	m_renderTarget->DrawEllipse(D2D1::Ellipse(
		D2D1::Point2F(center.x, center.y),
		horizontalRadius, verticalRadius),
		m_brush, STROKE_WIDTH);
}
