#pragma once
#include "SignalAliases.h"
#include <wx/listbox.h>

class Listbox : public wxListBox
{
public:
	Listbox(wxWindow* parent, int id);
	SignalConnection DoOnDeselection(SignalSlot callback);

private:
	wxDECLARE_EVENT_TABLE();
	void OnMouseLeftDown(wxMouseEvent&);

private:
	Signal m_deselectionSignal;
};
