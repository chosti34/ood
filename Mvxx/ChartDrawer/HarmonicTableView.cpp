#include "stdafx.h"
#include "HarmonicTableView.h"

HarmonicTableView::HarmonicTableView(wxWindow* parent)
	: wxListView(parent)
{
	AppendColumn("x");
	AppendColumn("y");
}

void HarmonicTableView::AddRowValues(const std::vector<std::string>& values)
{
	assert(values.size() == GetColumnCount());
	const long index = InsertItem(0, values.front());
	for (int i = 1; i < values.size(); ++i)
	{
		SetItem(index, i, values[i]);
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
