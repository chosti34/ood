#include "stdafx.h"
#include "HarmonicViewPanel.h"

HarmonicViewPanel::HarmonicViewPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	SetBackgroundColour(*wxWHITE);
}

void HarmonicViewPanel::OnPaint(wxPaintEvent&)
{
	wxPaintDC dc(this);
}

wxBEGIN_EVENT_TABLE(HarmonicViewPanel, wxPanel)
	EVT_PAINT(HarmonicViewPanel::OnPaint)
wxEND_EVENT_TABLE()
