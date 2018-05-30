#pragma once
#include <wx/panel.h>

class HarmonicSelectionPanel : public wxPanel
{
public:
	HarmonicSelectionPanel(wxWindow* parent);

private:
	wxDECLARE_EVENT_TABLE();
	void OnAddHarmonicButtonClick(wxCommandEvent&);
	void OnDeleteHarmonicButtonClick(wxCommandEvent&);

private:
	wxListBox* m_list;
	wxButton* m_addButton;
	wxButton* m_deleteButton;
};
