#include "stdafx.h"
#include "HarmonicSelectionView.h"
#include "AddHarmonicDialog.h"
#include <wx/statline.h>
#include <boost/format.hpp>

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
		% (harmonic.GetType() == HarmonicType::Sin ? "sin" : "cos")
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
	m_listbox = new Listbox(this, ListBoxCtrl);
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

SignalConnection HarmonicSelectionView::DoOnHarmonicInsertionClick(SignalSlot callback)
{
	return m_harmonicInsertionSignal.connect(callback);
}

SignalConnection HarmonicSelectionView::DoOnHarmonicDeletionClick(SignalSlot callback)
{
	return m_harmonicDeletionSignal.connect(callback);
}

SignalConnection HarmonicSelectionView::DoOnHarmonicSelectionClick(SignalSlot callback)
{
	return m_selectionChangeSignal.connect(callback);
}

SignalConnection HarmonicSelectionView::DoOnHarmonicDeselectionClick(SignalSlot callback)
{
	return m_listbox->DoOnDeselection(callback);
}

void HarmonicSelectionView::AppendHarmonic(const Harmonic& harmonic)
{
	m_listbox->Append(ToString(harmonic));
}

void HarmonicSelectionView::SetHarmonic(const Harmonic& harmonic, unsigned index)
{
	assert(index != wxNOT_FOUND);
	m_listbox->SetString(index, ToString(harmonic));
}

void HarmonicSelectionView::DeleteHarmonic(unsigned index)
{
	assert(index != wxNOT_FOUND);
	m_listbox->Delete(index);
}

int HarmonicSelectionView::GetSelection() const
{
	return m_listbox->GetSelection();
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
