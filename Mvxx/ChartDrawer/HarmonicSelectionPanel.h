#pragma once
#include <wx/panel.h>
#include <boost/signals2.hpp>
#include "Harmonic.h"

class HarmonicSelectionPanel : public wxPanel
{
public:
	HarmonicSelectionPanel(wxWindow* parent);

	boost::signals2::scoped_connection
		DoOnHarmonicSelection(boost::signals2::signal<void(int)>::slot_type callback);
	boost::signals2::scoped_connection
		DoOnHarmonicDeletion(boost::signals2::signal<void(int)>::slot_type callback);
	boost::signals2::scoped_connection
		DoOnHarmonicInsertion(boost::signals2::signal<void(const Harmonic&)>::slot_type callback);

	int GetListBoxSelectionIndex()const;
	void SetStringAtListBoxItem(const std::string& str, unsigned index);

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

	boost::signals2::signal<void(int)> m_selectionChangeSignal;
	boost::signals2::signal<void(int)> m_harmonicDeletionSignal;
	boost::signals2::signal<void(const Harmonic&)> m_harmonicInsertionSignal;
};
