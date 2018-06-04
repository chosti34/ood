#include "stdafx.h"
#include "Listbox.h"

Listbox::Listbox(wxWindow* parent, int id)
	: wxListBox(parent, id, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_ALWAYS_SB)
{
}

boost::signals2::connection Listbox::DoOnDeselection(
	boost::signals2::signal<void()>::slot_type callback)
{
	return m_deselectionSignal.connect(callback);
}

void Listbox::OnMouseLeftDown(wxMouseEvent& event)
{
	wxArrayInt selections;
	if (HitTest(event.GetPosition()) == wxNOT_FOUND && GetSelections(selections) != 0)
	{
		m_deselectionSignal();
		Deselect(wxNOT_FOUND);
	}
	event.Skip();
}

wxBEGIN_EVENT_TABLE(Listbox, wxListBox)
	EVT_LEFT_DOWN(Listbox::OnMouseLeftDown)
wxEND_EVENT_TABLE()
