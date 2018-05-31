#pragma once
#include <wx/panel.h>
#include <boost/signals2.hpp>
#include "Harmonic.h"

class HarmonicEditorPanel : public wxPanel
{
public:
	HarmonicEditorPanel(wxWindow* parent);

	void SetHarmonicData(const Harmonic& harmonic);
	Harmonic GetHarmonicData()const;

	boost::signals2::scoped_connection
		DoOnHarmonicAttributesChange(boost::signals2::signal<void()>::slot_type callback);

private:
	wxDECLARE_EVENT_TABLE();
	void OnAmplitudeCtrlChange(wxCommandEvent&);
	void OnFrequencyCtrlChange(wxCommandEvent&);
	void OnPhaseCtrlChange(wxCommandEvent&);
	void OnSinButtonClick(wxCommandEvent&);
	void OnCosButtonClick(wxCommandEvent&);

private:
	wxTextCtrl* m_amplitudeCtrl;
	wxTextCtrl* m_phaseCtrl;
	wxTextCtrl* m_frequencyCtrl;
	wxRadioButton* m_sinButton;
	wxRadioButton* m_cosButton;
	Harmonic m_harmonic;
	boost::signals2::signal<void()> m_attributesChangedSignal;
};
