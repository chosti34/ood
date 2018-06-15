#pragma once
#include <wx/textctrl.h>
#include <wx/string.h>
#include <wx/window.h>

namespace SharedUI
{
extern const unsigned FLOAT_PRECISION;

class FloatingPointTextCtrlCreator
{
public:
	void SetAdjustLayoutCallback(std::function<void(wxStaticText*, wxTextCtrl*, int)> && callback);
	wxTextCtrl* CreateTextCtrl(wxWindow* parent, int id, const wxString& label, long style = 0, int offset = 0);

private:
	std::function<void(wxStaticText*, wxTextCtrl*, int)> m_adjustLayout;
};
}
