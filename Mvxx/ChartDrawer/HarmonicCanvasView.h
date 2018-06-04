#pragma once
#include <wx/panel.h>
#include <vector>

class HarmonicCanvasView : public wxPanel
{
public:
	HarmonicCanvasView(wxWindow* parent);
	void SetPoints(const std::vector<wxRealPoint>& points);

private:
	wxDECLARE_EVENT_TABLE();
	void OnPaint(wxPaintEvent&);
	void OnResize(wxSizeEvent&);

private:
	std::vector<wxRealPoint> m_points;
};
