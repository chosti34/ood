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
	m_list = new wxListBox(this, ListBox, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_ALWAYS_SB);
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

boost::signals2::scoped_connection HarmonicSelectionPanel::DoOnHarmonicSelection(
	boost::signals2::signal<void(int)>::slot_type callback)
{
	return m_onSelectionChange.connect(callback);
}

boost::signals2::scoped_connection HarmonicSelectionPanel::DoOnHarmonicDeletion(
	boost::signals2::signal<void(int)>::slot_type callback)
{
	return m_onHarmonicDeletion.connect(callback);
}

boost::signals2::scoped_connection HarmonicSelectionPanel::DoOnHarmonicInsertion(
	boost::signals2::signal<void(const Harmonic&)>::slot_type callback)
{
	return m_onHarmonicInsertion.connect(callback);
}

void HarmonicSelectionPanel::OnAddHarmonicButtonClick(wxCommandEvent&)
{
	Harmonic harmonic;
	AddHarmonicDlg* dlg = new AddHarmonicDlg("Add New Harmonic", ADD_HARMONIC_DLG_SIZE, harmonic);
	if (dlg->ShowModal() == wxID_OK)
	{
		m_list->Append(harmonic.ToString());
		m_onHarmonicInsertion(harmonic);
	}
	dlg->Destroy();
}

void HarmonicSelectionPanel::OnDeleteHarmonicButtonClick(wxCommandEvent&)
{
	int selection = m_list->GetSelection();
	if (selection != -1)
	{
		m_list->Delete(selection);
		m_onHarmonicDeletion(selection);
	}
}

void HarmonicSelectionPanel::OnSelectionChange(wxCommandEvent&)
{
	m_onSelectionChange(m_list->GetSelection());
}

wxBEGIN_EVENT_TABLE(HarmonicSelectionPanel, wxPanel)
	EVT_BUTTON(AddHarmonic, HarmonicSelectionPanel::OnAddHarmonicButtonClick)
	EVT_BUTTON(DeleteHarmonic, HarmonicSelectionPanel::OnDeleteHarmonicButtonClick)
	EVT_LISTBOX(ListBox, HarmonicSelectionPanel::OnSelectionChange)
wxEND_EVENT_TABLE()
