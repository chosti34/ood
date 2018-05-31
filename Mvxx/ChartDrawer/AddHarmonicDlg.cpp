#include "stdafx.h"
#include "AddHarmonicDlg.h"
#include "StringUtils.h"

namespace
{
enum IDs
{
	SelectSinRadioButton,
	SelectCosRadioButton
};
}

AddHarmonicDlg::AddHarmonicDlg(const wxString& title, const wxSize& size, Harmonic& harmonic)
	: wxDialog(nullptr, wxID_ANY, title, wxDefaultPosition, size, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
	, m_harmonic(harmonic)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel* mainPanel = new wxPanel(this);

	// Amplitude
	wxStaticText* amplitudeText = new wxStaticText(mainPanel, wxID_ANY, "Amplitude:");
	m_amplitudeCtrl = new wxTextCtrl(
		mainPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0l,
		wxFloatingPointValidator<float>(3, &m_harmonic.amplitude));
	wxBoxSizer* amplitudeSizer = new wxBoxSizer(wxVERTICAL);
	amplitudeSizer->Add(amplitudeText, 0, wxALIGN_LEFT);
	amplitudeSizer->Add(m_amplitudeCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(amplitudeSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Frequency
	wxStaticText* frequencyText = new wxStaticText(mainPanel, wxID_ANY, "Frequency:");
	m_frequencyCtrl = new wxTextCtrl(mainPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0l,
		wxFloatingPointValidator<float>(3, &m_harmonic.frequency));
	wxBoxSizer* frequencySizer = new wxBoxSizer(wxVERTICAL);
	frequencySizer->Add(frequencyText, 0, wxALIGN_LEFT);
	frequencySizer->Add(m_frequencyCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(frequencySizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Phase
	wxStaticText* phaseText = new wxStaticText(mainPanel, wxID_ANY, "Phase:");
	m_phaseCtrl = new wxTextCtrl(mainPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0l,
		wxFloatingPointValidator<float>(3, &m_harmonic.phase));
	wxBoxSizer* phaseSizer = new wxBoxSizer(wxVERTICAL);
	phaseSizer->Add(phaseText, 0, wxALIGN_LEFT);
	phaseSizer->Add(m_phaseCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(phaseSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Harmonic type
	wxBoxSizer* radioSizer = new wxBoxSizer(wxHORIZONTAL);
	m_sinButton = new wxRadioButton(mainPanel, SelectSinRadioButton, wxT("Sin"));
	m_cosButton = new wxRadioButton(mainPanel, SelectCosRadioButton, wxT("Cos"));
	radioSizer->Add(m_sinButton, 0);
	radioSizer->Add(m_cosButton, 0, wxLEFT, 5);
	mainSizer->Add(radioSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Buttons
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* addButton = new wxButton(mainPanel, wxID_OK, wxT("Add"),
		wxDefaultPosition, wxSize(70, 30));
	wxButton* closeButton = new wxButton(mainPanel, wxID_CANCEL, wxT("Cancel"),
		wxDefaultPosition, wxSize(70, 30));
	buttonSizer->Add(addButton);
	buttonSizer->Add(closeButton, 0, wxLEFT, 5);
	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	mainPanel->SetSizerAndFit(mainSizer);
}

bool AddHarmonicDlg::TransferDataFromWindow()
{
	double amplitude = 0;
	double frequency = 0;
	double phase = 0;

	if (!m_amplitudeCtrl->GetValue().ToDouble(&amplitude) ||
		!m_frequencyCtrl->GetValue().ToDouble(&frequency) ||
		!m_phaseCtrl->GetValue().ToDouble(&phase))
	{
		return false;
	}

	m_harmonic.amplitude = float(amplitude);
	m_harmonic.frequency = float(frequency);
	m_harmonic.phase = float(phase);
	m_harmonic.type = m_sinButton->GetValue() ? Harmonic::Sin : Harmonic::Cos;
	return true;
}

bool AddHarmonicDlg::TransferDataToWindow()
{
	m_amplitudeCtrl->SetValue(StringUtils::FloatToString(m_harmonic.amplitude, 3));
	m_frequencyCtrl->SetValue(StringUtils::FloatToString(m_harmonic.frequency, 3));
	m_phaseCtrl->SetValue(StringUtils::FloatToString(m_harmonic.phase, 3));
	m_sinButton->SetValue(m_harmonic.type == Harmonic::Sin);
	m_cosButton->SetValue(m_harmonic.type == Harmonic::Cos);
	return true;
}
