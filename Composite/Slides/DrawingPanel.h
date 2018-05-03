#pragma once
#include <wx/panel.h>

class DrawingPanel : public wxPanel
{
public:
	DrawingPanel(wxFrame* frame);

private:
	void OnPaint(wxPaintEvent& event);

	wxDECLARE_EVENT_TABLE();
};
