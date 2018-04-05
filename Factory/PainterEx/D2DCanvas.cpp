#include "D2DCanvas.h"
#include <cassert>

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
	: m_pRenderTarget(nullptr)
	, m_pFactory(nullptr)
	, m_pBrush(nullptr)
{
	::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	auto hr = m_pFactory.CoCreateInstance(__uuidof(ID2D1Factory));
	assert(hr != S_FALSE); // Не возвращает S_OK

	hr = m_pRenderTarget.CoCreateInstance(__uuidof(ID2D1HwndRenderTarget));
	assert(hr != S_FALSE);

	hr = m_pBrush.CoCreateInstance(__uuidof(ID2D1SolidColorBrush));
	assert(hr != S_FALSE);

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	assert(hr == S_OK);

	RECT rect;
	auto res = GetClientRect(hWnd, &rect);
	assert(res != FALSE);
	(void)res;

	hr = m_pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rect.right, rect.bottom)),
		&m_pRenderTarget
	);
	assert(hr == S_OK);

	hr = m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Silver), &m_pBrush); // Цвет в любом случае будет изменён
	assert(hr == S_OK);
}

D2DCanvas::~D2DCanvas()
{
	::CoUninitialize();
}

void D2DCanvas::Resize(unsigned x, unsigned y)
{
	if (m_pRenderTarget)
	{
		m_pRenderTarget->Resize(D2D1::SizeU(x, y));
	}
}

void D2DCanvas::BeginDraw()
{
	m_pRenderTarget->BeginDraw();
}

void D2DCanvas::EndDraw()
{
	m_pRenderTarget->EndDraw();
}

void D2DCanvas::Clear(const Color& color)
{
	m_pRenderTarget->Clear(GetNormalizedColor(color));
}

void D2DCanvas::SetColor(const Color& color)
{
	m_pBrush->SetColor(GetNormalizedColor(color));
}

void D2DCanvas::DrawLine(const Point2D& from, const Point2D& to)
{
	m_pRenderTarget->DrawLine(
		D2D1::Point2F(from.x, from.y),
		D2D1::Point2F(to.x, to.y),
		m_pBrush, STROKE_WIDTH);
}

void D2DCanvas::DrawEllipse(const Point2D& center, float horizontalRadius, float verticalRadius)
{
	m_pRenderTarget->DrawEllipse(D2D1::Ellipse(
		D2D1::Point2F(center.x, center.y),
		horizontalRadius, verticalRadius),
		m_pBrush, STROKE_WIDTH);
}
