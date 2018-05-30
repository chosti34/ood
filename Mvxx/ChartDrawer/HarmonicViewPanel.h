#pragma once
#include <wx/panel.h>

class HarmonicViewPanel : public wxPanel
{
public:
	HarmonicViewPanel(wxWindow* parent);

private:
	wxDECLARE_EVENT_TABLE();
	void OnPaint(wxPaintEvent&);
};
