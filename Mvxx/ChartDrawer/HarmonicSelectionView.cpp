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
}

HarmonicSelectionView::HarmonicSelectionView(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	CreateControls();
}

boost::signals2::scoped_connection HarmonicSelectionView::DoOnHarmonicInsertionClick(
	boost::signals2::signal<void()>::slot_type callback)
{
	return m_harmonicInsertionSignal.connect(callback);
}

boost::signals2::scoped_connection HarmonicSelectionView::DoOnHarmonicDeletionClick(
	boost::signals2::signal<void()>::slot_type callback)
{
	return m_harmonicDeletionSignal.connect(callback);
}

boost::signals2::scoped_connection HarmonicSelectionView::DoOnHarmonicSelectionClick(
	boost::signals2::signal<void()>::slot_type callback)
{
	return m_selectionChangeSignal.connect(callback);
}

int HarmonicSelectionView::GetListBoxSelectionIndex()const
{
	return m_listbox->GetSelection();
}

void HarmonicSelectionView::SetStringAtListBoxItem(const std::string& str, unsigned index)
{
	m_listbox->SetString(index, str);
}

void HarmonicSelectionView::Append(const std::string& str)
{
	m_listbox->Append(str);
}

wxListBox* HarmonicSelectionView::GetListBox()
{
	return m_listbox;
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
	m_selectionChangeSignal();
}

void HarmonicSelectionView::OnAddHarmonicButtonClick(wxCommandEvent&)
{
	m_harmonicInsertionSignal();
}

void HarmonicSelectionView::OnDeleteHarmonicButtonClick(wxCommandEvent&)
{
	m_harmonicDeletionSignal();
}

wxBEGIN_EVENT_TABLE(HarmonicSelectionView, wxPanel)
	EVT_LISTBOX(ListBoxCtrl, HarmonicSelectionView::OnSelectionChange)
	EVT_BUTTON(AddHarmonicButton, HarmonicSelectionView::OnAddHarmonicButtonClick)
	EVT_BUTTON(DeleteHarmonicButton, HarmonicSelectionView::OnDeleteHarmonicButtonClick)
wxEND_EVENT_TABLE()
