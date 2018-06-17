#include "stdafx.h"
#include "HarmonicCanvasView.h"
#include "StringUtils.h"
#include "SharedUI.h"
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

const float CHART_OFFSET_HORIZONTAL = 50.f;
const float CHART_OFFSET_VERTICAL = 30.f;
}

HarmonicCanvasView::HarmonicCanvasView(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	SetBackgroundColour(*wxWHITE);
}

void HarmonicCanvasView::SetPixelPoints(const std::vector<wxRealPoint>& points)
{
	UpdateDrawingAreaSize();
	m_pixelPoints = ToGdiplusPoints(points);
	std::transform(m_pixelPoints.begin(), m_pixelPoints.end(), m_pixelPoints.begin(), [&](const PointF& point) {
		return PointF{ CHART_OFFSET_HORIZONTAL + point.X, (m_chartLinesCount / 2 + 1) * CHART_OFFSET_VERTICAL + point.Y };
	});
	Refresh(true);
}

wxSize HarmonicCanvasView::GetDrawingAreaSize()const
{
	return
	{
		static_cast<int>(GetSize().x - 2 * CHART_OFFSET_HORIZONTAL),
		static_cast<int>(GetSize().y - 2 * CHART_OFFSET_VERTICAL)
	};
}

void HarmonicCanvasView::UpdateDrawingAreaSize()
{
	m_chartLinesCount = GetSize().y / CHART_OFFSET_VERTICAL - 1;
	m_chartWidth = GetSize().x - 2 * CHART_OFFSET_HORIZONTAL;
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

	for (int i = 0; i < int(m_chartLinesCount); ++i)
	{
		Pen pen(Color(170, 170, 170), 1.f);
		pen.SetDashStyle(DashStyleDash);
		gfx.DrawLine(&pen,
			Point(CHART_OFFSET_HORIZONTAL, (i + 1) * CHART_OFFSET_VERTICAL),
			Point(CHART_OFFSET_HORIZONTAL + m_chartWidth, (i + 1) * CHART_OFFSET_VERTICAL));

		const std::wstring label = std::to_wstring(2 * int(m_chartLinesCount / 2) - 2 * i);
		const PointF origin = {
			CHART_OFFSET_HORIZONTAL - (10 * label.length()) / 2 - 10,
			(i + 1) * CHART_OFFSET_VERTICAL - 5.f };
		gfx.DrawString(label.c_str(), -1, &font, origin, &brush);
	}

	for (float x = CHART_OFFSET_HORIZONTAL; x <= m_chartWidth; x += 80.f)
	{
		const std::wstring label = StringUtils::FloatToWideString(
			static_cast<float>((x - CHART_OFFSET_HORIZONTAL) / SharedUI::PIXELS_PER_UNIT.x), 2);
		gfx.DrawString(label.c_str(), -1, &font, PointF(x, (m_chartLinesCount / 2 + 1) * CHART_OFFSET_VERTICAL + 5), &brush);
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
