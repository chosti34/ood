#include "stdafx.h"
#include "MainFrm.h"

namespace
{
const wxSize MAIN_FRAME_SIZE = { 640, 480 };
const wxString MAIN_FRAME_TITLE = "ChartDrawer";
}

class MyApp : public wxApp
{
public:
	bool OnInit() wxOVERRIDE
	{
		MainFrm* frame = new MainFrm(MAIN_FRAME_TITLE, MAIN_FRAME_SIZE);
		frame->Show(true);
		return true;
	}
};

#ifndef _DEBUG
	wxIMPLEMENT_APP(MyApp);
#else
	wxIMPLEMENT_APP_CONSOLE(MyApp);
#endif
