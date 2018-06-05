#include "stdafx.h"
#include "HarmonicPropertiesView.h"
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

const unsigned FLOAT_PRECISION = 3;
}

HarmonicPropertiesView::HarmonicPropertiesView(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* amplitudeText = new wxStaticText(this, wxID_ANY, "Amplitude:");
	m_amplitudeCtrl = new wxTextCtrl(this, AmplitudeCtrl, wxEmptyString, wxDefaultPosition, wxDefaultSize,
		wxTE_PROCESS_ENTER, wxFloatingPointValidator<float>(FLOAT_PRECISION));
	wxBoxSizer* amplitudeSizer = new wxBoxSizer(wxVERTICAL);
	amplitudeSizer->Add(amplitudeText, 0, wxALIGN_LEFT);
	amplitudeSizer->Add(m_amplitudeCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(amplitudeSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	wxStaticText* frequencyText = new wxStaticText(this, wxID_ANY, "Frequency:");
	m_frequencyCtrl = new wxTextCtrl(this, FrequencyCtrl, wxEmptyString, wxDefaultPosition, wxDefaultSize,
		wxTE_PROCESS_ENTER, wxFloatingPointValidator<float>(FLOAT_PRECISION));
	wxBoxSizer* frequencySizer = new wxBoxSizer(wxVERTICAL);
	frequencySizer->Add(frequencyText, 0, wxALIGN_LEFT);
	frequencySizer->Add(m_frequencyCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(frequencySizer, 0, wxALIGN_CENTER | wxTOP, 10);

	wxStaticText* phaseText = new wxStaticText(this, wxID_ANY, "Phase:");
	m_phaseCtrl = new wxTextCtrl(this, PhaseCtrl, wxEmptyString, wxDefaultPosition, wxDefaultSize,
		wxTE_PROCESS_ENTER, wxFloatingPointValidator<float>(FLOAT_PRECISION));
	wxBoxSizer* phaseSizer = new wxBoxSizer(wxVERTICAL);
	phaseSizer->Add(phaseText, 0, wxALIGN_LEFT);
	phaseSizer->Add(m_phaseCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(phaseSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	wxBoxSizer* radioSizer = new wxBoxSizer(wxHORIZONTAL);
	m_sinButton = new wxRadioButton(this, SinButton, wxT("Sin"));
	m_cosButton = new wxRadioButton(this, CosButton, wxT("Cos"));
	radioSizer->Add(m_sinButton, 0);
	radioSizer->Add(m_cosButton, 0, wxLEFT, 5);
	mainSizer->Add(radioSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	SetSizerAndFit(mainSizer);
}

SignalConnection HarmonicPropertiesView::DoOnHarmonicPropertiesChange(SignalSlot callback)
{
	return m_propertiesChangedSignal.connect(callback);
}

void HarmonicPropertiesView::SetHarmonicProperties(const Harmonic& harmonic)
{
	m_harmonic = harmonic;
	m_amplitudeCtrl->SetValue(StringUtils::FloatToString(m_harmonic.GetAmplitude(), FLOAT_PRECISION));
	m_frequencyCtrl->SetValue(StringUtils::FloatToString(m_harmonic.GetFrequency(), FLOAT_PRECISION));
	m_phaseCtrl->SetValue(StringUtils::FloatToString(m_harmonic.GetPhase(), FLOAT_PRECISION));
	m_sinButton->SetValue(m_harmonic.GetType() == HarmonicType::Sin);
	m_cosButton->SetValue(m_harmonic.GetType() == HarmonicType::Cos);
}

const Harmonic& HarmonicPropertiesView::GetHarmonicProperties()const
{
	return m_harmonic;
}

void HarmonicPropertiesView::OnAmplitudeCtrlChange(wxCommandEvent&)
{
	double value = 0;
	if (m_amplitudeCtrl->GetValue().ToDouble(&value))
	{
		m_harmonic.SetAmplitude(static_cast<float>(value));
		m_propertiesChangedSignal();
	}
}

void HarmonicPropertiesView::OnFrequencyCtrlChange(wxCommandEvent&)
{
	double value = 0;
	if (m_frequencyCtrl->GetValue().ToDouble(&value))
	{
		m_harmonic.SetFrequency(static_cast<float>(value));
		m_propertiesChangedSignal();
	}
}

void HarmonicPropertiesView::OnPhaseCtrlChange(wxCommandEvent&)
{
	double value = 0;
	if (m_phaseCtrl->GetValue().ToDouble(&value))
	{
		m_harmonic.SetPhase(static_cast<float>(value));
		m_propertiesChangedSignal();
	}
}

void HarmonicPropertiesView::OnSinButtonClick(wxCommandEvent&)
{
	m_harmonic.SetType(HarmonicType::Sin);
	m_propertiesChangedSignal();
}

void HarmonicPropertiesView::OnCosButtonClick(wxCommandEvent&)
{
	m_harmonic.SetType(HarmonicType::Cos);
	m_propertiesChangedSignal();
}

wxBEGIN_EVENT_TABLE(HarmonicPropertiesView, wxPanel)
	EVT_TEXT_ENTER(AmplitudeCtrl, HarmonicPropertiesView::OnAmplitudeCtrlChange)
	EVT_TEXT_ENTER(FrequencyCtrl, HarmonicPropertiesView::OnFrequencyCtrlChange)
	EVT_TEXT_ENTER(PhaseCtrl, HarmonicPropertiesView::OnPhaseCtrlChange)
	EVT_RADIOBUTTON(SinButton, HarmonicPropertiesView::OnSinButtonClick)
	EVT_RADIOBUTTON(CosButton, HarmonicPropertiesView::OnCosButtonClick)
wxEND_EVENT_TABLE()
