#include "stdafx.h"
#include "DrawingPanel.h"
#include <wx/dcgraph.h> // wxGCDC

namespace
{
class GraphicsDeviceContextAcquirer
{
public:
	GraphicsDeviceContextAcquirer(wxPaintDC& deviceContext)
		: m_graphicsDeviceContext(deviceContext)
		, m_hdc(nullptr)
		, m_acquired(false)
	{
	}

	~GraphicsDeviceContextAcquirer()
	{
		if (m_acquired)
		{
			m_graphicsDeviceContext.ReleaseHDC(m_hdc);
		}
	}

	WXHDC AcquireHDC()
	{
		if (m_acquired)
		{
			throw std::logic_error("HDC can be acquired only once");
		}
		m_hdc = m_graphicsDeviceContext.AcquireHDC();
		m_acquired = true;
		return m_hdc;
	}

	void ReleaseHDC()
	{
		if (!m_acquired)
		{
			throw std::logic_error("HDC must be acquired before releasing");
		}
		m_graphicsDeviceContext.ReleaseHDC(m_hdc);
		m_acquired = false;
		m_hdc = nullptr;
	}

private:
	bool m_acquired;
	wxGCDC m_graphicsDeviceContext;
	WXHDC m_hdc;
};
}

DrawingPanel::DrawingPanel(wxFrame* frame)
	: wxPanel(frame)
{
}

void DrawingPanel::AddDrawable(const std::shared_ptr<ICanvasDrawable>& drawable)
{
	m_drawables.push_back(drawable);
}

void DrawingPanel::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);
	PrepareDC(dc);

	GraphicsDeviceContextAcquirer acquirer(dc);
	Gdiplus::Graphics gfx(acquirer.AcquireHDC());
	gfx.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

	Canvas canvas(gfx);
	canvas.DrawEllipse({ 0, 0 }, 100, 50);
	canvas.SetFillColor(0xff0cf0cc);
	canvas.FillEllipse({ 0, 0 }, 100, 50);
	for (const auto& drawable : m_drawables)
	{
		drawable->Draw(canvas);
	}
}

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
	EVT_PAINT(DrawingPanel::OnPaint)
wxEND_EVENT_TABLE()
