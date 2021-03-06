#include "stdafx.h"
#include "HarmonicSelectionView.h"
#include "AddHarmonicDialog.h"
#include <boost/format.hpp>
#include <wx/statline.h>

namespace
{
enum IDs
{
	ListBoxCtrl = 1,
	AddHarmonicButton,
	DeleteHarmonicButton
};

std::string ToString(const Harmonic& harmonic)
{
	return (boost::format("%1%*%2%(%3%*x + %4%)")
		% harmonic.GetAmplitude()
		% ToString(harmonic.GetType())
		% harmonic.GetFrequency()
		% harmonic.GetPhase()).str();
}
}

HarmonicSelectionView::HarmonicSelectionView(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* title = new wxStaticText(this, wxID_ANY, "Harmonics");
	wxStaticLine* line = new wxStaticLine(this);
	m_listbox = new wxListBox(this, ListBoxCtrl, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_ALWAYS_SB);
	m_listbox->Bind(wxEVT_LEFT_DOWN, &HarmonicSelectionView::OnListboxMouseLeftDownClick, this);
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

SignalConnection HarmonicSelectionView::DoOnAppend(AppendSignal::slot_type callback)
{
	return m_appendSignal.connect(callback);
}

SignalConnection HarmonicSelectionView::DoOnDeletion(DeletionSignal::slot_type callback)
{
	return m_deletionSignal.connect(callback);
}

SignalConnection HarmonicSelectionView::DoOnSelection(SelectionSignal::slot_type callback)
{
	return m_selectionSignal.connect(callback);
}

SignalConnection HarmonicSelectionView::DoOnDeselection(DeselectionSignal::slot_type callback)
{
	return m_deselectionSignal.connect(callback);
}

void HarmonicSelectionView::Append(const Harmonic& harmonic)
{
	m_listbox->Append(ToString(harmonic));
}

void HarmonicSelectionView::SetElementAt(const Harmonic& harmonic, size_t index)
{
	assert(index < m_listbox->GetCount());
	m_listbox->SetString(index, ToString(harmonic));
}

void HarmonicSelectionView::DeleteElementAt(size_t index)
{
	assert(index < m_listbox->GetCount());
	m_listbox->Delete(index);
}

int HarmonicSelectionView::GetSelection()const
{
	return m_listbox->GetSelection();
}

void HarmonicSelectionView::OnSelectionChange(wxCommandEvent&)
{
	const int selection = m_listbox->GetSelection();
	assert(selection != wxNOT_FOUND);
	m_selectionSignal(selection);
}

void HarmonicSelectionView::OnAddHarmonicButtonClick(wxCommandEvent&)
{
	m_appendSignal();
}

void HarmonicSelectionView::OnDeleteHarmonicButtonClick(wxCommandEvent&)
{
	const int selection = m_listbox->GetSelection();
	if (selection != wxNOT_FOUND)
	{
		m_deletionSignal(selection);
	}
}

void HarmonicSelectionView::OnListboxMouseLeftDownClick(wxMouseEvent& event)
{
	wxArrayInt selections;
	if (m_listbox->GetSelections(selections) != 0 &&
		m_listbox->HitTest(event.GetPosition()) == wxNOT_FOUND)
	{
		m_listbox->Deselect(wxNOT_FOUND);
		m_deselectionSignal();
	}
	event.Skip();
}

wxBEGIN_EVENT_TABLE(HarmonicSelectionView, wxPanel)
	EVT_LISTBOX(ListBoxCtrl, HarmonicSelectionView::OnSelectionChange)
	EVT_BUTTON(AddHarmonicButton, HarmonicSelectionView::OnAddHarmonicButtonClick)
	EVT_BUTTON(DeleteHarmonicButton, HarmonicSelectionView::OnDeleteHarmonicButtonClick)
wxEND_EVENT_TABLE()
