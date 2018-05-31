#include "stdafx.h"
#include "HarmonicEditorPanel.h"
#include "StringUtils.h"
#include <wx/valnum.h>

namespace
{
enum IDs
{
	AmplitudeCtrl,
	FrequencyCtrl,
	PhaseCtrl,
	SinButton,
	CosButton
};
}

HarmonicEditorPanel::HarmonicEditorPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	CreateControls();
}

boost::signals2::scoped_connection
HarmonicEditorPanel::DoOnHarmonicAttributesChange(boost::signals2::signal<void()>::slot_type callback)
{
	return m_attributesChangedSignal.connect(callback);
}

void HarmonicEditorPanel::SetHarmonicData(const Harmonic& harmonic)
{
	m_harmonic = harmonic;
	m_amplitudeCtrl->SetValue(StringUtils::FloatToString(m_harmonic.amplitude, 3));
	m_frequencyCtrl->SetValue(StringUtils::FloatToString(m_harmonic.frequency, 3));
	m_phaseCtrl->SetValue(StringUtils::FloatToString(m_harmonic.phase, 3));
	m_sinButton->SetValue(m_harmonic.type == Harmonic::Sin);
	m_cosButton->SetValue(m_harmonic.type == Harmonic::Cos);
}

Harmonic HarmonicEditorPanel::GetHarmonicData()const
{
	return m_harmonic;
}

void HarmonicEditorPanel::CreateControls()
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Amplitude
	wxStaticText* amplitudeText = new wxStaticText(this, wxID_ANY, "Amplitude:");
	m_amplitudeCtrl = new wxTextCtrl(this, AmplitudeCtrl, wxEmptyString, wxDefaultPosition, wxDefaultSize,
		wxTE_PROCESS_ENTER, wxFloatingPointValidator<float>(3, &m_harmonic.amplitude));
	wxBoxSizer* amplitudeSizer = new wxBoxSizer(wxVERTICAL);
	amplitudeSizer->Add(amplitudeText, 0, wxALIGN_LEFT);
	amplitudeSizer->Add(m_amplitudeCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(amplitudeSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Frequency
	wxStaticText* frequencyText = new wxStaticText(this, wxID_ANY, "Frequency:");
	m_frequencyCtrl = new wxTextCtrl(this, FrequencyCtrl, wxEmptyString, wxDefaultPosition, wxDefaultSize,
		wxTE_PROCESS_ENTER, wxFloatingPointValidator<float>(3, &m_harmonic.frequency));
	wxBoxSizer* frequencySizer = new wxBoxSizer(wxVERTICAL);
	frequencySizer->Add(frequencyText, 0, wxALIGN_LEFT);
	frequencySizer->Add(m_frequencyCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(frequencySizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Phase
	wxStaticText* phaseText = new wxStaticText(this, wxID_ANY, "Phase:");
	m_phaseCtrl = new wxTextCtrl(this, PhaseCtrl, wxEmptyString, wxDefaultPosition, wxDefaultSize,
		wxTE_PROCESS_ENTER, wxFloatingPointValidator<float>(3, &m_harmonic.phase));
	wxBoxSizer* phaseSizer = new wxBoxSizer(wxVERTICAL);
	phaseSizer->Add(phaseText, 0, wxALIGN_LEFT);
	phaseSizer->Add(m_phaseCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(phaseSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Harmonic type
	wxBoxSizer* radioSizer = new wxBoxSizer(wxHORIZONTAL);
	m_sinButton = new wxRadioButton(this, SinButton, wxT("Sin"));
	m_cosButton = new wxRadioButton(this, CosButton, wxT("Cos"));
	radioSizer->Add(m_sinButton, 0);
	radioSizer->Add(m_cosButton, 0, wxLEFT, 5);
	mainSizer->Add(radioSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	SetSizerAndFit(mainSizer);
}

void HarmonicEditorPanel::OnAmplitudeCtrlChange(wxCommandEvent&)
{
	double value = 0;
	if (m_amplitudeCtrl->GetValue().ToDouble(&value))
	{
		m_harmonic.amplitude = static_cast<float>(value);
		m_attributesChangedSignal();
	}
}

void HarmonicEditorPanel::OnFrequencyCtrlChange(wxCommandEvent&)
{
	double value = 0;
	if (m_frequencyCtrl->GetValue().ToDouble(&value))
	{
		m_harmonic.frequency = static_cast<float>(value);
		m_attributesChangedSignal();
	}
}

void HarmonicEditorPanel::OnPhaseCtrlChange(wxCommandEvent&)
{
	double value = 0;
	if (m_phaseCtrl->GetValue().ToDouble(&value))
	{
		m_harmonic.phase = static_cast<float>(value);
		m_attributesChangedSignal();
	}
}

void HarmonicEditorPanel::OnSinButtonClick(wxCommandEvent&)
{
	m_harmonic.type = Harmonic::Sin;
	m_attributesChangedSignal();
}

void HarmonicEditorPanel::OnCosButtonClick(wxCommandEvent&)
{
	m_harmonic.type = Harmonic::Cos;
	m_attributesChangedSignal();
}

wxBEGIN_EVENT_TABLE(HarmonicEditorPanel, wxPanel)
	EVT_TEXT_ENTER(AmplitudeCtrl, HarmonicEditorPanel::OnAmplitudeCtrlChange)
	EVT_TEXT_ENTER(FrequencyCtrl, HarmonicEditorPanel::OnFrequencyCtrlChange)
	EVT_TEXT_ENTER(PhaseCtrl, HarmonicEditorPanel::OnPhaseCtrlChange)
	EVT_RADIOBUTTON(SinButton, HarmonicEditorPanel::OnSinButtonClick)
	EVT_RADIOBUTTON(CosButton, HarmonicEditorPanel::OnCosButtonClick)
wxEND_EVENT_TABLE()
