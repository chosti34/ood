#include "stdafx.h"
#include "HarmonicPropertiesView.h"
#include "StringUtils.h"
#include <wx/valnum.h>
#include <wx/statline.h>

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

const unsigned FLOAT_PRECISION = 3;

wxTextCtrl* CreateTextCtrlAndFit(
	wxWindow* parent, int id, const wxString& label, wxBoxSizer* mainSizer, int topOffset = 0)
{
	wxStaticText* text = new wxStaticText(parent, wxID_ANY, label);
	wxTextCtrl* ctrl = new wxTextCtrl(parent, id, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_PROCESS_ENTER, wxFloatingPointValidator<float>(FLOAT_PRECISION));
	wxBoxSizer* ctrlSizer = new wxBoxSizer(wxVERTICAL);
	ctrlSizer->Add(text, 0, wxALIGN_LEFT);
	ctrlSizer->Add(ctrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(ctrlSizer, 0, wxALIGN_CENTER | wxTOP, topOffset);
	return ctrl;
}
} // namespace

HarmonicPropertiesView::HarmonicPropertiesView(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* title = new wxStaticText(this, wxID_ANY, "Properties");
	wxStaticLine* separator = new wxStaticLine(this);
	mainSizer->Add(title, 0, wxEXPAND | wxLEFT | wxTOP, 5);
	mainSizer->Add(separator, 0, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);

	m_amplitudeCtrl = CreateTextCtrlAndFit(this, AmplitudeTextCtrl, "Amplitude:", mainSizer, 25);
	m_frequencyCtrl = CreateTextCtrlAndFit(this, FrequencyTextCtrl, "Frequency:", mainSizer, 15);
	m_phaseCtrl = CreateTextCtrlAndFit(this, PhaseTextCtrl, "Phase:", mainSizer, 15);

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

void HarmonicPropertiesView::UpdateHarmonicProperty(wxTextCtrl* ctrl, std::function<void(float)>&& callback)
{
	double value = 0;
	if (ctrl->GetValue().ToDouble(&value))
	{
		callback(static_cast<float>(value));
		m_propertiesChangedSignal();
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
	EVT_TEXT_ENTER(AmplitudeTextCtrl, HarmonicPropertiesView::OnAmplitudeCtrlPressEnter)
	EVT_TEXT_ENTER(FrequencyTextCtrl, HarmonicPropertiesView::OnFrequencyCtrlPressEnter)
	EVT_TEXT_ENTER(PhaseTextCtrl, HarmonicPropertiesView::OnPhaseCtrlPressEnter)
	EVT_RADIOBUTTON(SinRadioButton, HarmonicPropertiesView::OnSinButtonClick)
	EVT_RADIOBUTTON(CosRadioButton, HarmonicPropertiesView::OnCosButtonClick)
wxEND_EVENT_TABLE()
