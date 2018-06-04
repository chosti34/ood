#pragma once
#include <wx/panel.h>
#include <boost/signals2.hpp>
#include "Harmonic.h"

class HarmonicSelectionView : public wxPanel
{
public:
	HarmonicSelectionView(wxWindow* parent);

	boost::signals2::scoped_connection
		DoOnHarmonicInsertionClick(boost::signals2::signal<void()>::slot_type callback);
	boost::signals2::scoped_connection
		DoOnHarmonicDeletionClick(boost::signals2::signal<void()>::slot_type callback);
	boost::signals2::scoped_connection
		DoOnHarmonicSelectionClick(boost::signals2::signal<void()>::slot_type callback);

	int GetListBoxSelectionIndex()const;
	void SetStringAtListBoxItem(const std::string& str, unsigned index);
	void Append(const std::string& str);

	wxListBox* GetListBox();

private:
	void CreateControls();

	wxDECLARE_EVENT_TABLE();
	void OnSelectionChange(wxCommandEvent&);
	void OnAddHarmonicButtonClick(wxCommandEvent&);
	void OnDeleteHarmonicButtonClick(wxCommandEvent&);

private:
	wxListBox* m_listbox;
	wxButton* m_addButton;
	wxButton* m_deleteButton;

	boost::signals2::signal<void()> m_harmonicInsertionSignal;
	boost::signals2::signal<void()> m_harmonicDeletionSignal;
	boost::signals2::signal<void()> m_selectionChangeSignal;
};
