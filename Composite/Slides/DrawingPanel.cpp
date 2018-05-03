#include "stdafx.h"
#include "DrawingPanel.h"

DrawingPanel::DrawingPanel(wxFrame* frame)
	: wxPanel(frame)
{
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	dc.DrawEllipse(wxRect(100, 100, 300, 400));
}

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
	EVT_PAINT(DrawingPanel::OnPaint)
wxEND_EVENT_TABLE()
