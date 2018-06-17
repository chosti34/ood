#pragma once
#include "ITableView.h"
#include <wx/listctrl.h>

class HarmonicTableView : public wxListView, public ITableView
{
public:
	HarmonicTableView(wxWindow* parent);
	void SetPoints(const std::vector<wxRealPoint>& points) override;

private:
	void AdjustColumnsWidth();

	wxDECLARE_EVENT_TABLE();
	void OnResizeEvent(wxSizeEvent&);
};
