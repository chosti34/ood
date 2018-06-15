#pragma once
#include <wx/panel.h>
#include "SignalAliases.h"
#include "Harmonic.h"

class HarmonicPropertiesView : public wxPanel
{
public:
	HarmonicPropertiesView(wxWindow* parent);

	SignalConnection DoOnHarmonicPropertiesChange(SignalSlot callback);

	void SetHarmonicProperties(const Harmonic& harmonic);
	const Harmonic& GetHarmonicProperties()const;

private:
	void UpdateHarmonicProperty(wxTextCtrl* ctrl, std::function<void(float)>&& callback);

	wxDECLARE_EVENT_TABLE();
	void OnAmplitudeCtrlFocusLost(wxFocusEvent&);
	void OnFrequencyCtrlFocusLost(wxFocusEvent&);
	void OnPhaseCtrlFocusLost(wxFocusEvent&);

	void OnAmplitudeCtrlPressEnter(wxCommandEvent&);
	void OnFrequencyCtrlPressEnter(wxCommandEvent&);
	void OnPhaseCtrlPressEnter(wxCommandEvent&);

	void OnSinRadioButtonClick(wxCommandEvent&);
	void OnCosRadioButtonClick(wxCommandEvent&);

private:
	wxTextCtrl* m_amplitudeCtrl;
	wxTextCtrl* m_phaseCtrl;
	wxTextCtrl* m_frequencyCtrl;
	wxRadioButton* m_sinButton;
	wxRadioButton* m_cosButton;
	Harmonic m_harmonic;
	Signal m_propertiesChangedSignal;
};
