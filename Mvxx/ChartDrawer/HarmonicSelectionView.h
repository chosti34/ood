#pragma once
#include <wx/panel.h>
#include "SignalAliases.h"
#include "Harmonic.h"
#include "Listbox.h"

class HarmonicSelectionView : public wxPanel
{
public:
	HarmonicSelectionView(wxWindow* parent);

	SignalConnection DoOnHarmonicInsertionClick(SignalSlot callback);
	SignalConnection DoOnHarmonicDeletionClick(SignalSlot callback);
	SignalConnection DoOnHarmonicSelectionClick(SignalSlot callback);
	SignalConnection DoOnHarmonicDeselectionClick(SignalSlot callback);

	void AppendHarmonic(const Harmonic& harmonic);
	void SetHarmonic(const Harmonic& harmonic, unsigned index);
	void DeleteHarmonic(unsigned index);
	int GetSelection()const;

private:
	wxDECLARE_EVENT_TABLE();
	void OnSelectionChange(wxCommandEvent&);
	void OnAddHarmonicButtonClick(wxCommandEvent&);
	void OnDeleteHarmonicButtonClick(wxCommandEvent&);

private:
	Listbox* m_listbox;
	wxButton* m_addButton;
	wxButton* m_deleteButton;

	Signal m_harmonicInsertionSignal;
	Signal m_harmonicDeletionSignal;
	Signal m_selectionChangeSignal;
};
