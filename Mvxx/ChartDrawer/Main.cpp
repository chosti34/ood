#include "stdafx.h"
#include "MainFrame.h"
#include <wx/app.h>

class MyApp : public wxApp
{
public:
	bool OnInit() wxOVERRIDE
	{
		MainFrame* frame = new MainFrame(wxT("ChartDrawer"));
		frame->Show(true);
		return true;
	}
};

#ifndef _DEBUG
	wxIMPLEMENT_APP(MyApp);
#else
	wxIMPLEMENT_APP_CONSOLE(MyApp);
#endif
