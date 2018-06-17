#include "stdafx.h"
#include "HarmonicPropertiesView.h"
#include "StringUtils.h"
#include "SharedUI.h"
#include <wx/statline.h>
#include <wx/valnum.h>

namespace
{
enum IDs
{
	AmplitudeTextCtrl,
	FrequencyTextCtrl,
	PhaseTextCtrl,
	SinRadioButton,
	CosRadioButton
};
}

using namespace SharedUI;

HarmonicPropertiesView::HarmonicPropertiesView(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* title = new wxStaticText(this, wxID_ANY, "Properties");
	wxStaticLine* separator = new wxStaticLine(this);
	mainSizer->Add(title, 0, wxEXPAND | wxLEFT | wxTOP, 5);
	mainSizer->Add(separator, 0, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);

	m_amplitudeCtrl = new wxTextCtrl(this, AmplitudeTextCtrl, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_PROCESS_ENTER, wxFloatingPointValidator<float>(FLOAT_PRECISION));
	m_frequencyCtrl = new wxTextCtrl(this, FrequencyTextCtrl, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_PROCESS_ENTER, wxFloatingPointValidator<float>(FLOAT_PRECISION));
	m_phaseCtrl = new wxTextCtrl(this, PhaseTextCtrl, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_PROCESS_ENTER, wxFloatingPointValidator<float>(FLOAT_PRECISION));

	wxStaticText* m_amplitudeText = new wxStaticText(this, wxID_ANY, "Amplitude:");
	wxStaticText* m_frequencyText = new wxStaticText(this, wxID_ANY, "Frequency:");
	wxStaticText* m_phaseText = new wxStaticText(this, wxID_ANY, "Phase:");

	mainSizer->Add(AlignElements({ m_amplitudeText, m_amplitudeCtrl }, 2), 0, wxALIGN_CENTER | wxTOP, 25);
	mainSizer->Add(AlignElements({ m_frequencyText, m_frequencyCtrl }, 2), 0, wxALIGN_CENTER | wxTOP, 15);
	mainSizer->Add(AlignElements({ m_phaseText, m_phaseCtrl }, 2), 0, wxALIGN_CENTER | wxTOP, 15);

	m_amplitudeCtrl->Bind(wxEVT_KILL_FOCUS, &HarmonicPropertiesView::OnAmplitudeCtrlFocusLost, this);
	m_frequencyCtrl->Bind(wxEVT_KILL_FOCUS, &HarmonicPropertiesView::OnFrequencyCtrlFocusLost, this);
	m_phaseCtrl->Bind(wxEVT_KILL_FOCUS, &HarmonicPropertiesView::OnPhaseCtrlFocusLost, this);

	wxBoxSizer* radioSizer = new wxBoxSizer(wxHORIZONTAL);
	m_sinButton = new wxRadioButton(this, SinRadioButton, wxT("Sin"));
	m_cosButton = new wxRadioButton(this, CosRadioButton, wxT("Cos"));
	radioSizer->Add(m_sinButton, 0);
	radioSizer->Add(m_cosButton, 0, wxLEFT, 5);
	mainSizer->Add(radioSizer, 0, wxALIGN_CENTER | wxTOP, 15);

	SetSizerAndFit(mainSizer);
}

SignalConnection HarmonicPropertiesView::DoOnPropertiesChange(PropertiesChangeSignal::slot_type callback)
{
	return m_changeSignal.connect(callback);
}

void HarmonicPropertiesView::SetProperties(const Harmonic& harmonic, int index)
{
	m_harmonic = harmonic;
	m_selectionIndex = index;
	m_amplitudeCtrl->SetValue(StringUtils::FloatToString(m_harmonic.GetAmplitude(), FLOAT_PRECISION));
	m_frequencyCtrl->SetValue(StringUtils::FloatToString(m_harmonic.GetFrequency(), FLOAT_PRECISION));
	m_phaseCtrl->SetValue(StringUtils::FloatToString(m_harmonic.GetPhase(), FLOAT_PRECISION));
	m_sinButton->SetValue(m_harmonic.GetType() == HarmonicType::Sin);
	m_cosButton->SetValue(m_harmonic.GetType() == HarmonicType::Cos);
}

void HarmonicPropertiesView::Activate(bool activate)
{
	Enable(activate);
}

void HarmonicPropertiesView::UpdateHarmonicProperty(wxTextCtrl* ctrl, std::function<void(float)>&& callback)
{
	double value = 0;
	if (ctrl->GetValue().ToDouble(&value))
	{
		callback(static_cast<float>(value));
		m_changeSignal(m_harmonic, m_selectionIndex);
	}
}

void HarmonicPropertiesView::OnAmplitudeCtrlFocusLost(wxFocusEvent& event)
{
	UpdateHarmonicProperty(m_amplitudeCtrl, [this](float value) {
		m_harmonic.SetAmplitude(value);
	});
	event.Skip();
}

void HarmonicPropertiesView::OnFrequencyCtrlFocusLost(wxFocusEvent& event)
{
	UpdateHarmonicProperty(m_frequencyCtrl, [this](float value) {
		m_harmonic.SetFrequency(value);
	});
	event.Skip();
}

void HarmonicPropertiesView::OnPhaseCtrlFocusLost(wxFocusEvent& event)
{
	UpdateHarmonicProperty(m_phaseCtrl, [this](float value) {
		m_harmonic.SetPhase(value);
	});
	event.Skip();
}

void HarmonicPropertiesView::OnAmplitudeCtrlPressEnter(wxCommandEvent&)
{
	UpdateHarmonicProperty(m_amplitudeCtrl, [this](float value) {
		m_harmonic.SetAmplitude(value);
	});
}

void HarmonicPropertiesView::OnFrequencyCtrlPressEnter(wxCommandEvent&)
{
	UpdateHarmonicProperty(m_frequencyCtrl, [this](float value) {
		m_harmonic.SetFrequency(value);
	});
}

void HarmonicPropertiesView::OnPhaseCtrlPressEnter(wxCommandEvent&)
{
	UpdateHarmonicProperty(m_phaseCtrl, [this](float value) {
		m_harmonic.SetPhase(value);
	});
}

void HarmonicPropertiesView::OnSinRadioButtonClick(wxCommandEvent&)
{
	m_harmonic.SetType(HarmonicType::Sin);
	m_changeSignal(m_harmonic, m_selectionIndex);
}

void HarmonicPropertiesView::OnCosRadioButtonClick(wxCommandEvent&)
{
	m_harmonic.SetType(HarmonicType::Cos);
	m_changeSignal(m_harmonic, m_selectionIndex);
}

wxBEGIN_EVENT_TABLE(HarmonicPropertiesView, wxPanel)
	EVT_TEXT_ENTER(AmplitudeTextCtrl, HarmonicPropertiesView::OnAmplitudeCtrlPressEnter)
	EVT_TEXT_ENTER(FrequencyTextCtrl, HarmonicPropertiesView::OnFrequencyCtrlPressEnter)
	EVT_TEXT_ENTER(PhaseTextCtrl, HarmonicPropertiesView::OnPhaseCtrlPressEnter)
	EVT_RADIOBUTTON(SinRadioButton, HarmonicPropertiesView::OnSinRadioButtonClick)
	EVT_RADIOBUTTON(CosRadioButton, HarmonicPropertiesView::OnCosRadioButtonClick)
wxEND_EVENT_TABLE()
