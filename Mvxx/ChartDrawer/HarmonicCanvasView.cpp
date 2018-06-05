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
		return PointF{ 50 + static_cast<float>(point.x), static_cast<float>(point.y) + 30 * 5 };
	});
	return gdiplusPoints;
}
}

HarmonicCanvasView::HarmonicCanvasView(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	SetBackgroundColour(*wxWHITE);
}

void HarmonicCanvasView::SetPoints(const std::vector<wxRealPoint>& points)
{
	m_points = points;
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

	// drawing coordinate system and vertical labels
	for (int i = 0; i < 9; ++i)
	{
		Pen pen(Color(170, 170, 170), 1.f);
		pen.SetDashStyle(DashStyleDash);
		gfx.DrawLine(&pen, 50, (i + 1) * 30, 50 + 800, (i + 1) * 30);

		const std::wstring label = std::to_wstring(8 - 2 * i);
		const PointF origin = { 40.f - (10 * label.length()) / 2, (i + 1) * 30.f - 5.f };
		gfx.DrawString(label.c_str(), -1, &font, origin, &brush);
	}

	// drawing horizontal labels
	for (float x = 50; x <= 800; x += 80)
	{
		const std::wstring label = StringUtils::FloatToWideString((x - 50) / 100 * 1, 1);
		gfx.DrawString(label.c_str(), -1, &font, PointF(x, 5 * 30 + 5), &brush);
	}

	const std::vector<PointF> points = ToGdiplusPoints(m_points);
	Gdiplus::Pen pen(Gdiplus::Color(0, 0, 255), 1.5f);
	gfx.DrawCurve(&pen, points.data(), points.size());
}

void HarmonicCanvasView::OnResize(wxSizeEvent&)
{
	Refresh();
}

wxBEGIN_EVENT_TABLE(HarmonicCanvasView, wxPanel)
	EVT_PAINT(HarmonicCanvasView::OnPaint)
	EVT_SIZE(HarmonicCanvasView::OnResize)
wxEND_EVENT_TABLE()
