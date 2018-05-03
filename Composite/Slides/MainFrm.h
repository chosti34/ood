#pragma once
#include <wx/frame.h>

class MainFrm : public wxFrame
{
public:
	MainFrm(const wxString& title);

private:
	wxDECLARE_EVENT_TABLE();
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};
