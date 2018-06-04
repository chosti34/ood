#pragma once
#include <boost/signals2.hpp>
#include <wx/listbox.h>

class Listbox : public wxListBox
{
public:
	Listbox(wxWindow* parent, int id);

	boost::signals2::connection DoOnDeselection(
		boost::signals2::signal<void()>::slot_type callback);

private:
	wxDECLARE_EVENT_TABLE();
	void OnMouseLeftDown(wxMouseEvent&);

private:
	boost::signals2::signal<void()> m_deselectionSignal;
};
