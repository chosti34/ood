#include "stdafx.h"
#include "SharedUI.h"
#include <wx/valnum.h>

namespace SharedUI
{
const unsigned FLOAT_PRECISION = 3;

void FloatingPointTextCtrlCreator::SetAdjustLayoutCallback(std::function<void(wxStaticText*, wxTextCtrl*, int)>&& callback)
{
	m_adjustLayoutCallback = std::move(callback);
}

wxTextCtrl* FloatingPointTextCtrlCreator::CreateTextCtrl(wxWindow* parent, int id, const wxString& label, long style, int offset)
{
	wxStaticText* text = new wxStaticText(parent, wxID_ANY, label);
	wxTextCtrl* ctrl = new wxTextCtrl(parent, id, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, style, wxFloatingPointValidator<float>(FLOAT_PRECISION));
	if (m_adjustLayoutCallback)
	{
		m_adjustLayoutCallback(text, ctrl, offset);
	}
	return ctrl;
}
}
