#pragma once
#include "ITableView.h"
#include <wx/listctrl.h>

class HarmonicTableView : public wxListView, public ITableView
{
public:
	HarmonicTableView(wxWindow* parent);
	void AddRowValues(const std::vector<std::string>& values);

private:
	void AdjustColumnsWidth();

	wxDECLARE_EVENT_TABLE();
	void OnResizeEvent(wxSizeEvent&);
};
