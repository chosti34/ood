#include "stdafx.h"
#include "MainFrm.h"

namespace
{
enum
{
	MenuFileHelloItemID = 0
};
}

MainFrm::MainFrm(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	wxMenu* fileItem = new wxMenu;
	fileItem->Append(MenuFileHelloItemID, "&Hello...\tCtrl-H",
		"Help string shown in status bar for this menu item");
	fileItem->AppendSeparator();
	fileItem->Append(wxID_EXIT);

	wxMenu* helpItem = new wxMenu;
	helpItem->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(fileItem, "&File");
	menuBar->Append(helpItem, "&Help");

	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");
}

void MainFrm::OnHello(wxCommandEvent& WXUNUSED(event))
{
	wxLogMessage("Hello world from wxWidgets!");
}

void MainFrm::OnExit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void MainFrm::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox("Composite pattern with shapes example",
		"About Slides", wxOK | wxICON_INFORMATION);
}

wxBEGIN_EVENT_TABLE(MainFrm, wxFrame)
	EVT_MENU(MenuFileHelloItemID, MainFrm::OnHello)
	EVT_MENU(wxID_EXIT, MainFrm::OnExit)
	EVT_MENU(wxID_ABOUT, MainFrm::OnAbout)
wxEND_EVENT_TABLE()
