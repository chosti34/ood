#pragma once
#include <wx/panel.h>
#include "Harmonic.h"

class HarmonicEditorPanel : public wxPanel
{
public:
	HarmonicEditorPanel(wxWindow* parent);

	void SetHarmonic(const Harmonic* pHarmonic);
	bool TransferDataToWindow()override;

private:
	wxTextCtrl* m_amplitudeCtrl;
	wxTextCtrl* m_phaseCtrl;
	wxTextCtrl* m_frequencyCtrl;
	wxRadioButton* m_sinButton;
	wxRadioButton* m_cosButton;
	const Harmonic* m_pHarmonic;
};
