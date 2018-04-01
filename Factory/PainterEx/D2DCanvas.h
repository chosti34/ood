#pragma once
#include "../libpainter/ICanvas.h"
#include <d2d1.h>
#include <atlbase.h>

class D2DCanvas final : public ICanvas
{
public:
	D2DCanvas(HWND hWnd);
	~D2DCanvas();

	void Resize(unsigned x, unsigned y);
	void BeginDraw();
	void EndDraw();

	void Clear(const Color& color);
	void SetColor(const Color& color) override;
	void DrawLine(const Point2D& from, const Point2D& to) override;
	void DrawEllipse(const Point2D& center, float horizontalRadius, float verticalRadius) override;

private:
	CComPtr<ID2D1Factory> m_pFactory;
	CComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;
	CComPtr<ID2D1SolidColorBrush> m_pBrush;
};
