#pragma once
#include <wx/frame.h>
#include <wx/string.h>
#include "MainPanel.h"

class MainFrm : public wxFrame
{
public:
	MainFrm(const wxString& title, const wxSize& size);

private:
	MainPanel* m_panel;
};
