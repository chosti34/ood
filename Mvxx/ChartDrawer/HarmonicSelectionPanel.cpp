#include "stdafx.h"
#include "HarmonicSelectionPanel.h"
#include "AddHarmonicDlg.h"
#include <wx/statline.h>

namespace
{
enum IDs
{
	ListBox = 1,
	AddHarmonic,
	DeleteHarmonic
};

const wxSize ADD_HARMONIC_DLG_SIZE = { 280, 270 };
}

HarmonicSelectionPanel::HarmonicSelectionPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* title = new wxStaticText(this, wxID_ANY, "Harmonics");
	wxStaticLine* line = new wxStaticLine(this);
	m_list = new wxListBox(this, ListBox);
	m_addButton = new wxButton(this, AddHarmonic, "Add new");
	m_deleteButton = new wxButton(this, DeleteHarmonic, "Delete selected");

	mainSizer->Add(title, 0, wxLEFT | wxTOP, 5);
	mainSizer->Add(line, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 5);
	mainSizer->Add(m_list, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 5);

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(m_addButton);
	buttonSizer->Add(m_deleteButton, 0, wxLEFT, 5);
	mainSizer->Add(buttonSizer, 0, wxTOP | wxBOTTOM | wxLEFT, 5);

	SetSizerAndFit(mainSizer);
}

void HarmonicSelectionPanel::OnAddHarmonicButtonClick(wxCommandEvent&)
{
	AddHarmonicDlg* dlg = new AddHarmonicDlg("Add New Harmonic", ADD_HARMONIC_DLG_SIZE);
	dlg->ShowModal();
	dlg->Destroy();
}

void HarmonicSelectionPanel::OnDeleteHarmonicButtonClick(wxCommandEvent&)
{
	int selection = m_list->GetSelection();
	if (selection != -1)
	{
		m_list->Delete(selection);
	}
}

wxBEGIN_EVENT_TABLE(HarmonicSelectionPanel, wxPanel)
	EVT_BUTTON(AddHarmonic, HarmonicSelectionPanel::OnAddHarmonicButtonClick)
	EVT_BUTTON(DeleteHarmonic, HarmonicSelectionPanel::OnDeleteHarmonicButtonClick)
wxEND_EVENT_TABLE()
