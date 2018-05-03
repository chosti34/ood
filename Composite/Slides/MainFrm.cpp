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
	wxMenu* menuFileItem = new wxMenu;
	menuFileItem->Append(MenuFileHelloItemID, "&Hello...\tCtrl-H",
		"Help string shown in status bar for this menu item");
	menuFileItem->AppendSeparator();
	menuFileItem->Append(wxID_EXIT);

	wxMenu* menuHelpItem = new wxMenu;
	menuHelpItem->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFileItem, "&File");
	menuBar->Append(menuHelpItem, "&Help");

	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");
}

void MainFrm::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}

void MainFrm::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MainFrm::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets' Hello world sample",
		"About Hello World", wxOK | wxICON_INFORMATION);
}

wxBEGIN_EVENT_TABLE(MainFrm, wxFrame)
	EVT_MENU(MenuFileHelloItemID, MainFrm::OnHello)
	EVT_MENU(wxID_EXIT, MainFrm::OnExit)
	EVT_MENU(wxID_ABOUT, MainFrm::OnAbout)
wxEND_EVENT_TABLE()
