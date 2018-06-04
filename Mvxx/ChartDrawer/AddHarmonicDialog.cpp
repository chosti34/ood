#include "stdafx.h"
#include "AddHarmonicDialog.h"
#include "StringUtils.h"
#include <wx/valnum.h>

namespace
{
enum IDs
{
	SelectSinRadioButton,
	SelectCosRadioButton
};
}

AddHarmonicDialog::AddHarmonicDialog(const wxString& title, const wxSize& size, Harmonic& harmonic)
	: wxDialog(nullptr, wxID_ANY, title, wxDefaultPosition, size, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
	, m_harmonic(harmonic)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel* panel = new wxPanel(this);

	wxStaticText* amplitudeText = new wxStaticText(panel, wxID_ANY, "Amplitude:");
	m_amplitudeCtrl = new wxTextCtrl(
		panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0,
		wxFloatingPointValidator<float>(3, &m_harmonic.amplitude));
	wxBoxSizer* amplitudeSizer = new wxBoxSizer(wxVERTICAL);
	amplitudeSizer->Add(amplitudeText, 0, wxALIGN_LEFT);
	amplitudeSizer->Add(m_amplitudeCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(amplitudeSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	wxStaticText* frequencyText = new wxStaticText(panel, wxID_ANY, "Frequency:");
	m_frequencyCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0,
		wxFloatingPointValidator<float>(3, &m_harmonic.frequency));
	wxBoxSizer* frequencySizer = new wxBoxSizer(wxVERTICAL);
	frequencySizer->Add(frequencyText, 0, wxALIGN_LEFT);
	frequencySizer->Add(m_frequencyCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(frequencySizer, 0, wxALIGN_CENTER | wxTOP, 10);

	wxStaticText* phaseText = new wxStaticText(panel, wxID_ANY, "Phase:");
	m_phaseCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0,
		wxFloatingPointValidator<float>(3, &m_harmonic.phase));
	wxBoxSizer* phaseSizer = new wxBoxSizer(wxVERTICAL);
	phaseSizer->Add(phaseText, 0, wxALIGN_LEFT);
	phaseSizer->Add(m_phaseCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(phaseSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	wxBoxSizer* radioSizer = new wxBoxSizer(wxHORIZONTAL);
	m_sinButton = new wxRadioButton(panel, SelectSinRadioButton, wxT("Sin"));
	m_cosButton = new wxRadioButton(panel, SelectCosRadioButton, wxT("Cos"));
	radioSizer->Add(m_sinButton, 0);
	radioSizer->Add(m_cosButton, 0, wxLEFT, 5);
	mainSizer->Add(radioSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* addButton = new wxButton(panel, wxID_OK, wxT("Add"), // OK button will be handled automatically
		wxDefaultPosition, wxSize(70, 30));
	wxButton* closeButton = new wxButton(panel, wxID_CANCEL, wxT("Cancel"),
		wxDefaultPosition, wxSize(70, 30));
	buttonSizer->Add(addButton);
	buttonSizer->Add(closeButton, 0, wxLEFT, 5);
	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	panel->SetSizerAndFit(mainSizer);
}

bool AddHarmonicDialog::TransferDataFromWindow()
{
	double values[3];
	if (m_amplitudeCtrl->GetValue().ToDouble(&values[0]) &&
		m_frequencyCtrl->GetValue().ToDouble(&values[1]) &&
		m_phaseCtrl->GetValue().ToDouble(&values[2]) &&
		(m_sinButton->GetValue() || m_cosButton->GetValue()))
	{
		m_harmonic.amplitude = static_cast<float>(values[0]);
		m_harmonic.frequency = static_cast<float>(values[1]);
		m_harmonic.phase = static_cast<float>(values[2]);
		m_harmonic.type = m_sinButton->GetValue() ? Harmonic::Sin : Harmonic::Cos;
		return true;
	}
	return false;
}

bool AddHarmonicDialog::TransferDataToWindow()
{
	m_amplitudeCtrl->SetValue(StringUtils::FloatToString(m_harmonic.amplitude, 3));
	m_frequencyCtrl->SetValue(StringUtils::FloatToString(m_harmonic.frequency, 3));
	m_phaseCtrl->SetValue(StringUtils::FloatToString(m_harmonic.phase, 3));
	m_sinButton->SetValue(m_harmonic.type == Harmonic::Sin);
	m_cosButton->SetValue(m_harmonic.type == Harmonic::Cos);
	return true;
}
