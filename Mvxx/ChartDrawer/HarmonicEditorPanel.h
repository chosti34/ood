#pragma once
#include <wx/panel.h>

class HarmonicEditorPanel : public wxPanel
{
public:
	HarmonicEditorPanel(wxWindow* parent);

private:
	wxTextCtrl* m_amplitudeCtrl;
	wxTextCtrl* m_phaseCtrl;
	wxTextCtrl* m_frequencyCtrl;
	wxRadioButton* m_sinButton;
	wxRadioButton* m_cosButton;
};
