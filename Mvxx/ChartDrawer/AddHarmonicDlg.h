#pragma once
#include <wx/dialog.h>
#include <wx/string.h>
#include <wx/radiobut.h>
#include <wx/textctrl.h>

class AddHarmonicDlg : public wxDialog
{
public:
	AddHarmonicDlg(const wxString& title, const wxSize& size);

private:
	wxDECLARE_EVENT_TABLE();
	void OnAddButtonClick(wxCommandEvent&);

private:
	wxTextCtrl* m_amplitudeCtrl;
	wxTextCtrl* m_phaseCtrl;
	wxTextCtrl* m_frequencyCtrl;
	wxRadioButton* m_sinButton;
	wxRadioButton* m_cosButton;
};
