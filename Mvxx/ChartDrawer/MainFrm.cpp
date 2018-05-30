#include "stdafx.h"
#include "MainFrm.h"

MainFrm::MainFrm(const wxString& title, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, size)
{
	m_panel = new MainPanel(this);
	CreateStatusBar();
	Center();
}
