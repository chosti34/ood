#include "stdafx.h"
#include "AddHarmonicDlg.h"

namespace
{
enum IDs
{
	AddHarmonic = 1 // Add button id
};
}

AddHarmonicDlg::AddHarmonicDlg(const wxString& title, const wxSize& size)
	: wxDialog(nullptr, wxID_ANY, title, wxDefaultPosition, size, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel* mainPanel = new wxPanel(this);

	// Amplitude
	wxStaticText* amplitudeText = new wxStaticText(mainPanel, wxID_ANY, "Amplitude:");
	m_amplitudeCtrl = new wxTextCtrl(mainPanel, wxID_ANY);
	wxBoxSizer* amplitudeSizer = new wxBoxSizer(wxVERTICAL);
	amplitudeSizer->Add(amplitudeText, 0, wxALIGN_LEFT);
	amplitudeSizer->Add(m_amplitudeCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(amplitudeSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Frequency
	wxStaticText* frequencyText = new wxStaticText(mainPanel, wxID_ANY, "Frequency:");
	m_frequencyCtrl = new wxTextCtrl(mainPanel, wxID_ANY);
	wxBoxSizer* frequencySizer = new wxBoxSizer(wxVERTICAL);
	frequencySizer->Add(frequencyText, 0, wxALIGN_LEFT);
	frequencySizer->Add(m_frequencyCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(frequencySizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Phase
	wxStaticText* phaseText = new wxStaticText(mainPanel, wxID_ANY, "Phase:");
	m_phaseCtrl = new wxTextCtrl(mainPanel, wxID_ANY);
	wxBoxSizer* phaseSizer = new wxBoxSizer(wxVERTICAL);
	phaseSizer->Add(phaseText, 0, wxALIGN_LEFT);
	phaseSizer->Add(m_phaseCtrl, 0, wxALIGN_LEFT | wxTOP, 2);
	mainSizer->Add(phaseSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Harmonic type
	wxBoxSizer* radioSizer = new wxBoxSizer(wxHORIZONTAL);
	m_sinButton = new wxRadioButton(mainPanel, wxID_ANY, wxT("Sin"));
	m_cosButton = new wxRadioButton(mainPanel, wxID_ANY, wxT("Cos"));
	radioSizer->Add(m_sinButton, 0);
	radioSizer->Add(m_cosButton, 0, wxLEFT, 5);
	mainSizer->Add(radioSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	// Buttons
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* addButton = new wxButton(mainPanel, AddHarmonic, wxT("Add"),
		wxDefaultPosition, wxSize(70, 30));
	wxButton* closeButton = new wxButton(mainPanel, wxID_CANCEL, wxT("Cancel"),
		wxDefaultPosition, wxSize(70, 30));
	buttonSizer->Add(addButton);
	buttonSizer->Add(closeButton, 0, wxLEFT, 5);
	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxTOP, 10);

	mainPanel->SetSizerAndFit(mainSizer);
}

void AddHarmonicDlg::OnAddButtonClick(wxCommandEvent&)
{
	// TODO: implement this
}

wxBEGIN_EVENT_TABLE(AddHarmonicDlg, wxDialog)
	EVT_BUTTON(AddHarmonic, AddHarmonicDlg::OnAddButtonClick)
wxEND_EVENT_TABLE()
