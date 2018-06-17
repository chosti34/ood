#pragma once
#include <wx/panel.h>
#include "ICanvasView.h"
#include <gdiplustypes.h>

class HarmonicCanvasView : public wxPanel , public ICanvasView
{
public:
	HarmonicCanvasView(wxWindow* parent);
	void SetPixelPoints(const std::vector<wxRealPoint>& points) override;
	wxSize GetDrawingAreaSize()const override;
	void UpdateDrawingAreaSize()override;

private:
	wxDECLARE_EVENT_TABLE();
	void OnPaint(wxPaintEvent&);
	void OnResize(wxSizeEvent&);

private:
	std::vector<Gdiplus::PointF> m_pixelPoints;
	unsigned m_chartLinesCount;
	float m_chartWidth;
	std::unique_ptr<Gdiplus::FontFamily> m_fontFamily;
	std::unique_ptr<Gdiplus::Font> m_font;
};
