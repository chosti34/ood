#pragma once
#include <wx/frame.h>
#include <wx/string.h>
#include "MainPanel.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title, const wxSize& size);
	MainPanel* GetMainPanel();

private:
	MainPanel* m_panel;
};
