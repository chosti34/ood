#include "stdafx.h"
#include "HarmonicTableView.h"

HarmonicTableView::HarmonicTableView(wxWindow* parent)
	: wxListView(parent)
{
	AppendColumn("x");
	AppendColumn("y");
}

void HarmonicTableView::SetPoints(const std::vector<wxRealPoint>& points)
{
	DeleteAllItems();
	for (const auto& point : points)
	{
		long index = InsertItem(GetItemCount() + 1, std::to_string(point.x));
		SetItem(index, 1, std::to_string(point.y));
	}
}

void HarmonicTableView::AdjustColumnsWidth()
{
	for (int i = 0; i < GetColumnCount(); ++i)
	{
		SetColumnWidth(i, GetClientSize().x / GetColumnCount());
	}
}

void HarmonicTableView::OnResizeEvent(wxSizeEvent&)
{
	AdjustColumnsWidth();
}

wxBEGIN_EVENT_TABLE(HarmonicTableView, wxListView)
	EVT_SIZE(HarmonicTableView::OnResizeEvent)
wxEND_EVENT_TABLE()
