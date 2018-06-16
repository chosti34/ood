#pragma once
#include "Harmonic.h"
#include "IPropertiesView.h"
#include <wx/panel.h>

class HarmonicPropertiesView
	: public wxPanel
	, public IPropertiesView<Harmonic>
{
public:
	HarmonicPropertiesView(wxWindow* parent);

	SignalConnection DoOnPropertiesChange(PropertiesChangeSignal::slot_type callback) override;
	void SetProperties(const Harmonic& harmonic, int index) override;

	void Activate(bool activate) override;

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
	PropertiesChangeSignal m_changeSignal;
	Harmonic m_harmonic;
	int m_selectionIndex;
};
