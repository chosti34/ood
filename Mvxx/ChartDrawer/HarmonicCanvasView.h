#pragma once
#include <wx/panel.h>
#include "ICanvasView.h"

class HarmonicCanvasView : public wxPanel , public ICanvasView
{
public:
	HarmonicCanvasView(wxWindow* parent);
	void SetPixelPoints(const std::vector<wxRealPoint>& points) override;

private:
	wxDECLARE_EVENT_TABLE();
	void OnPaint(wxPaintEvent&);
	void OnResize(wxSizeEvent&);

private:
	std::vector<Gdiplus::PointF> m_pixelPoints;
};
