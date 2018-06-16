#pragma once
#include <wx/panel.h>
#include "Signals.h"
#include "Harmonic.h"

class HarmonicPropertiesView : public wxPanel
{
	using PropertiesChangeSignal = Signal<void(const Harmonic&)>;

public:
	HarmonicPropertiesView(wxWindow* parent);

	SignalConnection DoOnHarmonicPropertiesChange(PropertiesChangeSignal::slot_type callback);
	void SetHarmonicProperties(const Harmonic& harmonic);

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
	PropertiesChangeSignal m_propertiesChangeSignal;
};
