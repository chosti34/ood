#include "stdafx.h"
#include "HarmonicCanvasView.h"

namespace
{
const std::pair<float, float> SCALE_X = { 1.f, 50.f };
const std::pair<float, float> SCALE_Y = { 1.f, 50.f };
}

HarmonicCanvasView::HarmonicCanvasView(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	SetBackgroundColour(*wxWHITE);
}

void HarmonicCanvasView::SetPoints(const std::vector<wxRealPoint>& points)
{
	m_points = points;
}

void HarmonicCanvasView::OnPaint(wxPaintEvent&)
{
	wxPaintDC dc(this);
	dc.SetPen(wxPen(wxColour(255, 0, 0), 3, wxPENSTYLE_SOLID));

	for (const auto& point : m_points)
	{
		wxPoint pixel(
			point.x / SCALE_X.first * SCALE_X.second,
			-(point.y / SCALE_Y.first * SCALE_Y.second) + dc.GetSize().y / 2);
		dc.DrawPoint(pixel);
	}
}

void HarmonicCanvasView::OnResize(wxSizeEvent&)
{
	Refresh();
}

wxBEGIN_EVENT_TABLE(HarmonicCanvasView, wxPanel)
	EVT_PAINT(HarmonicCanvasView::OnPaint)
	EVT_SIZE(HarmonicCanvasView::OnResize)
wxEND_EVENT_TABLE()
