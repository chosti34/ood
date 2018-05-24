#pragma once
#include <wx/panel.h>
#include <wx/listbox.h>
#include <wx/button.h>

class MainPanel : public wxPanel
{
public:
	MainPanel(wxFrame* frame);

private:
	void OnAddHarmonicButtonClick(wxCommandEvent&);
	void OnDeleteHarmonicButtonClick(wxCommandEvent&);

private:
	wxListBox* m_listBox;
	wxButton* m_addHarmonicButton;
	wxButton* m_deleteHarmonicButton;
};
