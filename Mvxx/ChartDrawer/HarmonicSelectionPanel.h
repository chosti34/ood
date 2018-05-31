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
	wxDECLARE_EVENT_TABLE();
	void OnAddHarmonicButtonClick(wxCommandEvent&);
	void OnDeleteHarmonicButtonClick(wxCommandEvent&);
	void OnSelectionChange(wxCommandEvent&);

private:
	wxListBox* m_list;
	wxButton* m_addButton;
	wxButton* m_deleteButton;

	boost::signals2::signal<void(int)> m_onSelectionChange;
	boost::signals2::signal<void(int)> m_onHarmonicDeletion;
	boost::signals2::signal<void(const Harmonic&)> m_onHarmonicInsertion;
};
