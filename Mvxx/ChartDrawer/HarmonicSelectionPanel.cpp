#include "stdafx.h"
#include "HarmonicSelectionPanel.h"
#include "AddHarmonicDialog.h"
#include <wx/statline.h>

namespace
{
enum IDs
{
	ListBoxCtrl = 1,
	AddHarmonicButton,
	DeleteHarmonicButton
};

const wxSize ADD_HARMONIC_DLG_SIZE = { 280, 270 };
}

HarmonicSelectionPanel::HarmonicSelectionPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	CreateControls();
}

boost::signals2::scoped_connection HarmonicSelectionPanel::DoOnHarmonicSelection(
	boost::signals2::signal<void(int)>::slot_type callback)
{
	return m_selectionChangeSignal.connect(callback);
}

boost::signals2::scoped_connection HarmonicSelectionPanel::DoOnHarmonicDeletion(
	boost::signals2::signal<void(int)>::slot_type callback)
{
	return m_harmonicDeletionSignal.connect(callback);
}

boost::signals2::scoped_connection HarmonicSelectionPanel::DoOnHarmonicInsertion(
	boost::signals2::signal<void(const Harmonic&)>::slot_type callback)
{
	return m_harmonicInsertionSignal.connect(callback);
}

int HarmonicSelectionPanel::GetListBoxSelectionIndex()const
{
	return m_listbox->GetSelection();
}

void HarmonicSelectionPanel::SetStringAtListBoxItem(const std::string& str, unsigned index)
{
	m_listbox->SetString(index, str);
}

void HarmonicSelectionPanel::CreateControls()
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* title = new wxStaticText(this, wxID_ANY, "Harmonics");
	wxStaticLine* line = new wxStaticLine(this);
	m_listbox = new wxListBox(this, ListBoxCtrl, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_ALWAYS_SB);
	m_addButton = new wxButton(this, AddHarmonicButton, "Add new");
	m_deleteButton = new wxButton(this, DeleteHarmonicButton, "Delete selected");

	mainSizer->Add(title, 0, wxLEFT | wxTOP, 5);
	mainSizer->Add(line, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 5);
	mainSizer->Add(m_listbox, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 5);

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(m_addButton);
	buttonSizer->Add(m_deleteButton, 0, wxLEFT, 5);
	mainSizer->Add(buttonSizer, 0, wxTOP | wxBOTTOM | wxLEFT, 5);

	SetSizerAndFit(mainSizer);
}

void HarmonicSelectionPanel::OnSelectionChange(wxCommandEvent&)
{
	m_selectionChangeSignal(m_listbox->GetSelection());
}

void HarmonicSelectionPanel::OnAddHarmonicButtonClick(wxCommandEvent&)
{
	Harmonic harmonic;
	AddHarmonicDialog* dlg = new AddHarmonicDialog("Add New Harmonic", ADD_HARMONIC_DLG_SIZE, harmonic);
	if (dlg->ShowModal() == wxID_OK)
	{
		m_listbox->Append(harmonic.ToString());
		m_harmonicInsertionSignal(harmonic);
	}
	dlg->Destroy();
}

void HarmonicSelectionPanel::OnDeleteHarmonicButtonClick(wxCommandEvent&)
{
	int selection = m_listbox->GetSelection();
	if (selection != -1)
	{
		m_listbox->Delete(selection);
		m_harmonicDeletionSignal(selection);
	}
}

wxBEGIN_EVENT_TABLE(HarmonicSelectionPanel, wxPanel)
	EVT_LISTBOX(ListBoxCtrl, HarmonicSelectionPanel::OnSelectionChange)
	EVT_BUTTON(AddHarmonicButton, HarmonicSelectionPanel::OnAddHarmonicButtonClick)
	EVT_BUTTON(DeleteHarmonicButton, HarmonicSelectionPanel::OnDeleteHarmonicButtonClick)
wxEND_EVENT_TABLE()
