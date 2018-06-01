#pragma once
#include <wx/panel.h>
#include <vector>

class HarmonicViewPanel : public wxPanel
{
public:
	HarmonicViewPanel(wxWindow* parent);
	void SetPoints(const std::vector<wxRealPoint>& points);

private:
	wxDECLARE_EVENT_TABLE();
	void OnPaint(wxPaintEvent&);
	void OnResize(wxSizeEvent&);

private:
	std::vector<wxRealPoint> m_points;
};
