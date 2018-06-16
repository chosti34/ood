#include "stdafx.h"
#include "HarmonicCanvasView.h"
#include "StringUtils.h"
#include <wx/dcgraph.h>

using namespace Gdiplus;

namespace
{
class HDCAcquirer
{
public:
	HDCAcquirer(wxGCDC& ctx)
		: m_ctx(ctx)
	{
	}

	~HDCAcquirer()
	{
		if (m_hdc)
		{
			m_ctx.ReleaseHDC(m_hdc);
		}
	}

	WXHDC Acquire()
	{
		if (m_hdc)
		{
			throw std::logic_error("hdc cannot be acquired twice");
		}
		m_hdc = m_ctx.AcquireHDC();
		return m_hdc;
	}

	void Release()
	{
		if (!m_hdc)
		{
			throw std::logic_error("hdc must be acquired before releasing");
		}
		m_ctx.ReleaseHDC(m_hdc);
		m_hdc = nullptr;
	}

private:
	WXHDC m_hdc = nullptr;
	wxGCDC& m_ctx;
};

std::vector<PointF> ToGdiplusPoints(const std::vector<wxRealPoint>& points)
{
	std::vector<PointF> gdiplusPoints(points.size());
	std::transform(points.begin(), points.end(), gdiplusPoints.begin(), [](const wxRealPoint& point) {
		return PointF{ static_cast<float>(point.x), static_cast<float>(point.y) };
	});
	return gdiplusPoints;
}

const unsigned CHART_LINES_COUNT = 9;
const float CHART_WIDTH = 800.f;
const float CHART_OFFSET_HORIZONTAL = 50.f;
const float CHART_OFFSET_VERTICAL = 30.f;
const float CHART_CENTER_VERTICAL = (CHART_LINES_COUNT / 2 + 1) * CHART_OFFSET_VERTICAL;
}

HarmonicCanvasView::HarmonicCanvasView(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	SetBackgroundColour(*wxWHITE);
}

void HarmonicCanvasView::SetPixelPoints(const std::vector<wxRealPoint>& points)
{
	m_pixelPoints = ToGdiplusPoints(points);
	// Adjust for our view offset
	std::transform(m_pixelPoints.begin(), m_pixelPoints.end(), m_pixelPoints.begin(), [](const PointF& point) {
		return PointF{ CHART_OFFSET_HORIZONTAL + point.X, CHART_CENTER_VERTICAL + point.Y };
	});
	Refresh(true);
}

void HarmonicCanvasView::OnPaint(wxPaintEvent&)
{
	wxGCDC ctx(wxPaintDC(this));
	HDCAcquirer acquirer(ctx);
	Graphics gfx(acquirer.Acquire());
	gfx.SetSmoothingMode(SmoothingModeAntiAlias);

	SolidBrush brush(Color(140, 140, 140));
	FontFamily fontFamily(L"Consolas");
	Font font(&fontFamily, 10, FontStyleRegular, UnitPixel);

	for (int i = 0; i < CHART_LINES_COUNT; ++i)
	{
		Pen pen(Color(170, 170, 170), 1.f);
		pen.SetDashStyle(DashStyleDash);
		gfx.DrawLine(&pen, CHART_OFFSET_HORIZONTAL,
			(i + 1) * CHART_OFFSET_VERTICAL,
			CHART_OFFSET_HORIZONTAL + CHART_WIDTH,
			(i + 1) * CHART_OFFSET_VERTICAL);

		const std::wstring label = std::to_wstring(8 - 2 * i);
		const PointF origin = { 40.f - (10 * label.length()) / 2, (i + 1) * 30.f - 5.f };
		gfx.DrawString(label.c_str(), -1, &font, origin, &brush);
	}

	for (float x = 50; x <= CHART_WIDTH; x += 80)
	{
		const std::wstring label = StringUtils::FloatToWideString((x - 50) / 100 * 1, 1);
		gfx.DrawString(label.c_str(), -1, &font, PointF(x, 5 * 30 + 5), &brush);
	}

	Gdiplus::Pen pen(Gdiplus::Color(0, 0, 255), 1.5f);
	gfx.DrawCurve(&pen, m_pixelPoints.data(), m_pixelPoints.size());
}

void HarmonicCanvasView::OnResize(wxSizeEvent&)
{
	Refresh(true);
}

wxBEGIN_EVENT_TABLE(HarmonicCanvasView, wxPanel)
	EVT_PAINT(HarmonicCanvasView::OnPaint)
	EVT_SIZE(HarmonicCanvasView::OnResize)
wxEND_EVENT_TABLE()
