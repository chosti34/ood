#include "stdafx.h"
#include <wx/wx.h>

class Simple : public wxFrame
{
public:
	Simple(const wxString& title)
		: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150))
	{
		Centre();
	}
};

class MyApp : public wxApp
{
public:
	bool OnInit() wxOVERRIDE
	{
		Simple *simple = new Simple(wxT("Simple"));
		simple->Show(true);
		return true;
	}
};

#ifndef _DEBUG
	wxIMPLEMENT_APP(MyApp);
#else
	wxIMPLEMENT_APP_CONSOLE(MyApp);
#endif
