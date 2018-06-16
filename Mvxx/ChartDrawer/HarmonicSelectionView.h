#pragma once
#include <wx/panel.h>
#include "Signals.h"
#include "Harmonic.h"

class HarmonicSelectionView : public wxPanel
{
	using InsertionClickSignal = Signal<void()>;
	using DeletionClickSignal = Signal<void(int)>;
	using SelectionSignal = Signal<void(int)>;
	using DeselectionSignal = Signal<void()>;

public:
	HarmonicSelectionView(wxWindow* parent);

	SignalConnection DoOnHarmonicInsertionClick(InsertionClickSignal::slot_type callback);
	SignalConnection DoOnHarmonicDeletionClick(DeletionClickSignal::slot_type callback);
	SignalConnection DoOnHarmonicSelectionClick(SelectionSignal::slot_type callback);
	SignalConnection DoOnHarmonicDeselectionClick(DeselectionSignal::slot_type callback);

	void AppendHarmonic(const Harmonic& harmonic);
	void SetHarmonic(const Harmonic& harmonic, unsigned index);
	void DeleteHarmonic(unsigned index);
	int GetSelection()const;

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
	InsertionClickSignal m_harmonicInsertionSignal;
	DeletionClickSignal m_harmonicDeletionSignal;
	SelectionSignal m_selectionChangeSignal;
	DeselectionSignal m_deselectionSignal;
};
