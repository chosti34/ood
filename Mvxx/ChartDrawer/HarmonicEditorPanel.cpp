#include "stdafx.h"
#include "HarmonicEditorPanel.h"

HarmonicEditorPanel::HarmonicEditorPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Amplitude
	wxStaticText* amplitudeText = new wxStaticText(this, wxID_ANY, "Amplitude:");
	m_amplitudeCtrl = new wxTextCtrl(this, wxID_ANY);
	wxBoxSizer* amplitudeSizer = new wxBoxSizer(wxVERTICAL);
	amplitudeSizer->Add(amplitudeText, 0, wxALIGN_LEFT);
	amplitudeSizer->Add(m_amplitudeCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(amplitudeSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Frequency
	wxStaticText* frequencyText = new wxStaticText(this, wxID_ANY, "Frequency:");
	m_frequencyCtrl = new wxTextCtrl(this, wxID_ANY);
	wxBoxSizer* frequencySizer = new wxBoxSizer(wxVERTICAL);
	frequencySizer->Add(frequencyText, 0, wxALIGN_LEFT);
	frequencySizer->Add(m_frequencyCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(frequencySizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Phase
	wxStaticText* phaseText = new wxStaticText(this, wxID_ANY, "Phase:");
	m_phaseCtrl = new wxTextCtrl(this, wxID_ANY);
	wxBoxSizer* phaseSizer = new wxBoxSizer(wxVERTICAL);
	phaseSizer->Add(phaseText, 0, wxALIGN_LEFT);
	phaseSizer->Add(m_phaseCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(phaseSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Harmonic type
	wxBoxSizer* radioSizer = new wxBoxSizer(wxHORIZONTAL);
	m_sinButton = new wxRadioButton(this, wxID_ANY, wxT("Sin"));
	m_cosButton = new wxRadioButton(this, wxID_ANY, wxT("Cos"));
	radioSizer->Add(m_sinButton, 0);
	radioSizer->Add(m_cosButton, 0, wxLEFT, 5);
	mainSizer->Add(radioSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	SetSizerAndFit(mainSizer);
}
