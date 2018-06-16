#include "stdafx.h"
#include "AddHarmonicDialog.h"
#include "StringUtils.h"
#include "SharedUI.h"

namespace
{
enum IDs
{
	SelectSinRadioButton,
	SelectCosRadioButton
};

const wxSize BUTTON_SIZE = { 70, 30 };

bool GetValue(wxTextCtrl* ctrl, double& value)
{
	return ctrl->GetValue().ToDouble(&value);
}

bool AnyOfHasValue(const std::initializer_list<wxRadioButton*> && buttons)
{
	bool value = false;
	for (const auto& button : buttons)
	{
		value |= button->GetValue();
	}
	return value;
}
}

AddHarmonicDialog::AddHarmonicDialog(const wxString& title, const wxSize& size, Harmonic& harmonic)
	: wxDialog(nullptr, wxID_ANY, title, wxDefaultPosition, size, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
	, m_harmonic(harmonic)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel* panel = new wxPanel(this);

	auto creator = std::make_unique<SharedUI::FloatingPointTextCtrlCreator>();
	creator->SetAdjustLayoutCallback([&mainSizer](wxStaticText* text, wxTextCtrl* ctrl, int offset) {
		wxBoxSizer* ctrlSizer = new wxBoxSizer(wxVERTICAL);
		ctrlSizer->Add(text, 0, wxALIGN_LEFT);
		ctrlSizer->Add(ctrl, 0, wxALIGN_LEFT | wxTOP, 2);
		mainSizer->Add(ctrlSizer, 0, wxALIGN_CENTER | wxTOP, offset);
	});

	m_amplitudeCtrl = creator->CreateTextCtrl(panel, wxID_ANY, "Amplitude:", 0, 10);
	m_frequencyCtrl = creator->CreateTextCtrl(panel, wxID_ANY, "Frequency:", 0, 10);
	m_phaseCtrl = creator->CreateTextCtrl(panel, wxID_ANY, "Phase:", 0, 10);

	wxBoxSizer* radioSizer = new wxBoxSizer(wxHORIZONTAL);
	m_sinButton = new wxRadioButton(panel, SelectSinRadioButton, wxT("Sin"));
	m_cosButton = new wxRadioButton(panel, SelectCosRadioButton, wxT("Cos"));
	radioSizer->Add(m_sinButton, 0);
	radioSizer->Add(m_cosButton, 0, wxLEFT, 5);
	mainSizer->Add(radioSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* addButton = new wxButton(panel, wxID_OK, wxT("Add"), wxDefaultPosition, BUTTON_SIZE);
	wxButton* closeButton = new wxButton(panel, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, BUTTON_SIZE);
	buttonSizer->Add(addButton);
	buttonSizer->Add(closeButton, 0, wxLEFT, 5);
	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	panel->SetSizerAndFit(mainSizer);
}

bool AddHarmonicDialog::TransferDataFromWindow()
{
	double values[3];
	if (GetValue(m_amplitudeCtrl, values[0]) &&
		GetValue(m_frequencyCtrl, values[1]) &&
		GetValue(m_phaseCtrl, values[2]) &&
		AnyOfHasValue({ m_sinButton, m_cosButton }))
	{
		m_harmonic.SetAmplitude(static_cast<float>(values[0]));
		m_harmonic.SetFrequency(static_cast<float>(values[1]));
		m_harmonic.SetPhase(static_cast<float>(values[2]));
		m_harmonic.SetType(m_sinButton->GetValue() ? HarmonicType::Sin : HarmonicType::Cos);
		return true;
	}
	return false;
}

bool AddHarmonicDialog::TransferDataToWindow()
{
	m_amplitudeCtrl->SetValue(StringUtils::FloatToString(m_harmonic.GetAmplitude(), SharedUI::FLOAT_PRECISION));
	m_frequencyCtrl->SetValue(StringUtils::FloatToString(m_harmonic.GetFrequency(), SharedUI::FLOAT_PRECISION));
	m_phaseCtrl->SetValue(StringUtils::FloatToString(m_harmonic.GetPhase(), SharedUI::FLOAT_PRECISION));
	m_sinButton->SetValue(m_harmonic.GetType() == HarmonicType::Sin);
	m_cosButton->SetValue(m_harmonic.GetType() == HarmonicType::Cos);
	return true;
}
