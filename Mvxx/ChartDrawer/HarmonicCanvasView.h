#pragma once
#include <wx/panel.h>
#include <vector>

class HarmonicCanvasView : public wxPanel
{
public:
	HarmonicCanvasView(wxWindow* parent);
	void SetPixelPoints(const std::vector<wxRealPoint>& pixelPoints);

private:
	wxDECLARE_EVENT_TABLE();
	void OnPaint(wxPaintEvent&);
	void OnResize(wxSizeEvent&);

private:
	std::vector<Gdiplus::PointF> m_pixelPoints;
};
