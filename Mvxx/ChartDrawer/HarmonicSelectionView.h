#pragma once
#include <wx/panel.h>
#include "Harmonic.h"
#include "Listbox.h"

class HarmonicSelectionView : public wxPanel
{
public:
	HarmonicSelectionView(wxWindow* parent);

	boost::signals2::connection DoOnHarmonicInsertionClick(
		boost::signals2::signal<void()>::slot_type callback);
	boost::signals2::connection DoOnHarmonicDeletionClick(
		boost::signals2::signal<void()>::slot_type callback);
	boost::signals2::connection DoOnHarmonicSelectionClick(
		boost::signals2::signal<void()>::slot_type callback);
	boost::signals2::connection DoOnHarmonicDeselectionClick(
		boost::signals2::signal<void()>::slot_type callback);

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

	boost::signals2::signal<void()> m_harmonicInsertionSignal;
	boost::signals2::signal<void()> m_harmonicDeletionSignal;
	boost::signals2::signal<void()> m_selectionChangeSignal;
};
