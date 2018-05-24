#include "stdafx.h"
#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, size)
{
	m_panel = new MainPanel(this);
	Center();
}
