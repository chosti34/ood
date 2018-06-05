#include "stdafx.h"
#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, size)
{
	m_panel = new MainPanel(this);
	CreateStatusBar();
	Center();
	wxInitAllImageHandlers();
	SetIcon(wxIcon("icon.png", wxBITMAP_TYPE_PNG));
}

MainPanel* MainFrame::GetMainPanel()
{
	return m_panel;
}
