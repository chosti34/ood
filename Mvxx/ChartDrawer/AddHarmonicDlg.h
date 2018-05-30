#pragma once
#include <wx/dialog.h>
#include <wx/string.h>
#include <wx/radiobut.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>
#include "Harmonic.h"

class AddHarmonicDlg : public wxDialog
{
public:
	AddHarmonicDlg(const wxString& title, const wxSize& size, Harmonic& harmonic);

	bool TransferDataFromWindow() override;
	bool TransferDataToWindow() override;

private:
	wxTextCtrl* m_amplitudeCtrl;
	wxTextCtrl* m_phaseCtrl;
	wxTextCtrl* m_frequencyCtrl;
	wxRadioButton* m_sinButton;
	wxRadioButton* m_cosButton;
	Harmonic& m_harmonic;
};
