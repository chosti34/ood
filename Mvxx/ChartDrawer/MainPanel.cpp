#include "stdafx.h"
#include "MainPanel.h"

#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include <wx/stattext.h>
#include <wx/radiobut.h>
#include <wx/statline.h>

MainPanel::MainPanel(wxFrame* frame)
	: wxPanel(frame)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

	// HARMONIC SELECTION PANEL
	wxPanel* selectHarmonicPanel = new wxPanel(this);
	selectHarmonicPanel->SetBackgroundColour(wxColour(200, 200, 200));

	wxStaticText* listBoxTitle = new wxStaticText(selectHarmonicPanel, wxID_ANY, wxT("Harmonics"));
	wxStaticLine* line = new wxStaticLine(selectHarmonicPanel);
	line->Show(true);
	m_listBox = new wxListBox(selectHarmonicPanel, 1);
	m_addHarmonicButton = new wxButton(selectHarmonicPanel, 2, wxT("Add new"));
	m_deleteHarmonicButton = new wxButton(selectHarmonicPanel, 3, wxT("Delete selected"));

	wxBoxSizer* selectHarmonicSizer = new wxBoxSizer(wxVERTICAL);
	selectHarmonicSizer->Add(listBoxTitle, 0, wxTOP | wxLEFT, 5);
	selectHarmonicSizer->Add(line, 0, wxEXPAND | wxRIGHT | wxLEFT, 5);
	selectHarmonicSizer->Add(m_listBox, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(m_addHarmonicButton, 0, wxALIGN_CENTER | wxALL, 5);
	buttonSizer->Add(m_deleteHarmonicButton, 0, wxALIGN_CENTER | wxALL, 5);
	selectHarmonicSizer->Add(buttonSizer);

	selectHarmonicPanel->SetSizerAndFit(selectHarmonicSizer);
	mainSizer->Add(selectHarmonicPanel, 1, wxEXPAND | wxALL, 5);

	// HARMONIC EDITOR PANEL
	wxBoxSizer* harmonicEditorSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel* harmonicEditorPanel = new wxPanel(this);
	harmonicEditorPanel->SetBackgroundColour(wxColour(155, 155, 155));

	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* amplitudeTextLabel = new wxStaticText(harmonicEditorPanel, wxID_ANY, wxT("Amplitude:"));
	wxTextCtrl* amplitudeTextCtrl = new wxTextCtrl(harmonicEditorPanel, 4);
	hbox1->Add(amplitudeTextLabel, 0, wxALIGN_TOP, 0);
	hbox1->Add(amplitudeTextCtrl, 0, wxALIGN_TOP, 0);
	harmonicEditorSizer->Add(hbox1);

	wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* frequencyTextLabel = new wxStaticText(harmonicEditorPanel, wxID_ANY, wxT("Frequency:"));
	wxTextCtrl* frequenceTextCtrl = new wxTextCtrl(harmonicEditorPanel, 4);
	hbox2->Add(frequencyTextLabel, 0, wxALIGN_TOP, 0);
	hbox2->Add(frequenceTextCtrl, 0, wxALIGN_TOP, 0);
	harmonicEditorSizer->Add(hbox2);

	wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* phaseTextLabel = new wxStaticText(harmonicEditorPanel, wxID_ANY, wxT("Phase:"));
	wxTextCtrl* phaseTextCtrl = new wxTextCtrl(harmonicEditorPanel, 4);
	hbox3->Add(phaseTextLabel, 0, wxALIGN_TOP, 0);
	hbox3->Add(phaseTextCtrl, 0, wxALIGN_TOP, 0);
	harmonicEditorSizer->Add(hbox3);

	harmonicEditorPanel->SetSizerAndFit(harmonicEditorSizer);
	mainSizer->Add(harmonicEditorPanel, 1, wxEXPAND | wxALL, 5);

	SetSizerAndFit(mainSizer);

	Connect(2, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainPanel::OnAddHarmonicButtonClick));
	Connect(3, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainPanel::OnDeleteHarmonicButtonClick));
}

void MainPanel::OnAddHarmonicButtonClick(wxCommandEvent&)
{
	wxString input = wxGetTextFromUser(wxT("Add new item"));
	if (!input.IsEmpty())
	{
		m_listBox->Append(input);
	}
}

void MainPanel::OnDeleteHarmonicButtonClick(wxCommandEvent&)
{
	int selection = m_listBox->GetSelection();
	if (selection != -1)
	{
		m_listBox->Delete(selection);
	}
	else
	{
		wxMessageBox(wxT("Select harmonic to delete"));
	}
}
