#pragma once
#include <wx/panel.h>
#include <boost/signals2.hpp>
#include "Harmonic.h"

class HarmonicPropertiesView : public wxPanel
{
public:
	HarmonicPropertiesView(wxWindow* parent);

	boost::signals2::scoped_connection
		DoOnHarmonicAttributesChange(boost::signals2::signal<void()>::slot_type callback);

	void SetHarmonicProperties(const Harmonic& harmonic);
	Harmonic GetHarmonicProperties()const;

private:
	void CreateControls();

	wxDECLARE_EVENT_TABLE();
	void OnAmplitudeCtrlChange(wxCommandEvent&);
	void OnFrequencyCtrlChange(wxCommandEvent&);
	void OnPhaseCtrlChange(wxCommandEvent&);
	void OnSinButtonClick(wxCommandEvent&);
	void OnCosButtonClick(wxCommandEvent&);

private:
	// current harmonic data
	Harmonic m_harmonic;

	wxTextCtrl* m_amplitudeCtrl;
	wxTextCtrl* m_phaseCtrl;
	wxTextCtrl* m_frequencyCtrl;
	wxRadioButton* m_sinButton;
	wxRadioButton* m_cosButton;

	boost::signals2::signal<void()> m_attributesChangedSignal;
};
