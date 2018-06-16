#pragma once
#include "ISelectionView.h"
#include "Harmonic.h"
#include <wx/panel.h>

class HarmonicSelectionView
	: public wxPanel
	, public ISelectionView<Harmonic>
{
public:
	HarmonicSelectionView(wxWindow* parent);

	SignalConnection DoOnAppend(AppendSignal::slot_type callback) override;
	SignalConnection DoOnDeletion(DeletionSignal::slot_type callback) override;
	SignalConnection DoOnSelection(SelectionSignal::slot_type callback) override;
	SignalConnection DoOnDeselection(DeselectionSignal::slot_type callback) override;

	void Append(const Harmonic& harmonic) override;
	void SetElementAt(const Harmonic& harmonic, size_t index) override;
	void DeleteElementAt(size_t index) override;
	int GetSelection()const override;

private:
	wxDECLARE_EVENT_TABLE();
	void OnSelectionChange(wxCommandEvent&);
	void OnAddHarmonicButtonClick(wxCommandEvent&);
	void OnDeleteHarmonicButtonClick(wxCommandEvent&);
	void OnListboxMouseLeftDownClick(wxMouseEvent&);

private:
	wxListBox* m_listbox;
	wxButton* m_addButton;
	wxButton* m_deleteButton;
	AppendSignal m_appendSignal;
	DeletionSignal m_deletionSignal;
	SelectionSignal m_selectionSignal;
	DeselectionSignal m_deselectionSignal;
};
