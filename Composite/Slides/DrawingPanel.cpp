#include "stdafx.h"
#include "DrawingPanel.h"

DrawingPanel::DrawingPanel(wxFrame* frame)
	: wxPanel(frame)
	, m_canvas(std::make_unique<Canvas>())
{
}

void DrawingPanel::AddDrawable(const std::shared_ptr<ICanvasDrawable>& drawable)
{
	m_drawables.push_back(drawable);
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	dc.DrawEllipse(wxRect(100, 100, 300, 400));
	for (const auto& drawable : m_drawables)
	{
		drawable->Draw(*m_canvas);
	}
}

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
	EVT_PAINT(DrawingPanel::OnPaint)
wxEND_EVENT_TABLE()
