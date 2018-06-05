#pragma once
#include <wx/dialog.h>
#include <wx/string.h>
#include <wx/radiobut.h>
#include <wx/textctrl.h>
#include "Harmonic.h"

class AddHarmonicDialog : public wxDialog
{
public:
	AddHarmonicDialog(const wxString& title, const wxSize& size, Harmonic& harmonic);

	bool TransferDataFromWindow() override;
	bool TransferDataToWindow() override;

private:
	Harmonic& m_harmonic;
	wxTextCtrl* m_amplitudeCtrl;
	wxTextCtrl* m_phaseCtrl;
	wxTextCtrl* m_frequencyCtrl;
	wxRadioButton* m_sinButton;
	wxRadioButton* m_cosButton;
};
