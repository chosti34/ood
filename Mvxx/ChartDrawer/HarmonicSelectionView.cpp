#include "stdafx.h"
#include "HarmonicSelectionView.h"
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

HarmonicSelectionView::HarmonicSelectionView(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	CreateControls();
}

boost::signals2::scoped_connection HarmonicSelectionView::DoOnHarmonicSelection(
	boost::signals2::signal<void(int)>::slot_type callback)
{
	return m_selectionChangeSignal.connect(callback);
}

boost::signals2::scoped_connection HarmonicSelectionView::DoOnHarmonicDeletion(
	boost::signals2::signal<void(int)>::slot_type callback)
{
	return m_harmonicDeletionSignal.connect(callback);
}

boost::signals2::scoped_connection HarmonicSelectionView::DoOnHarmonicInsertion(
	boost::signals2::signal<void(const Harmonic&)>::slot_type callback)
{
	return m_harmonicInsertionSignal.connect(callback);
}

int HarmonicSelectionView::GetListBoxSelectionIndex()const
{
	return m_listbox->GetSelection();
}

void HarmonicSelectionView::SetStringAtListBoxItem(const std::string& str, unsigned index)
{
	m_listbox->SetString(index, str);
}

void HarmonicSelectionView::CreateControls()
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

void HarmonicSelectionView::OnSelectionChange(wxCommandEvent&)
{
	m_selectionChangeSignal(m_listbox->GetSelection());
}

void HarmonicSelectionView::OnAddHarmonicButtonClick(wxCommandEvent&)
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

void HarmonicSelectionView::OnDeleteHarmonicButtonClick(wxCommandEvent&)
{
	int selection = m_listbox->GetSelection();
	if (selection != -1)
	{
		m_listbox->Delete(selection);
		m_harmonicDeletionSignal(selection);
	}
}

wxBEGIN_EVENT_TABLE(HarmonicSelectionView, wxPanel)
	EVT_LISTBOX(ListBoxCtrl, HarmonicSelectionView::OnSelectionChange)
	EVT_BUTTON(AddHarmonicButton, HarmonicSelectionView::OnAddHarmonicButtonClick)
	EVT_BUTTON(DeleteHarmonicButton, HarmonicSelectionView::OnDeleteHarmonicButtonClick)
wxEND_EVENT_TABLE()
