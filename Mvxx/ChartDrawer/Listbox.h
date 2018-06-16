#pragma once
#include "Signals.h"
#include <wx/listbox.h>

class Listbox : public wxListBox
{
	using DeselectionSignal = Signal<void()>;

public:
	Listbox(wxWindow* parent, int id);
	SignalConnection DoOnDeselection(DeselectionSignal::slot_type callback);

private:
	wxDECLARE_EVENT_TABLE();
	void OnMouseLeftDown(wxMouseEvent&);

private:
	DeselectionSignal m_deselectionSignal;
};
