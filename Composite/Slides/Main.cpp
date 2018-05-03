#include "stdafx.h"
#include "MainFrm.h"

class App : public wxApp
{
public:
	bool OnInit()wxOVERRIDE
	{
		MainFrm* frame = new MainFrm("Slides", wxPoint(50, 50), wxSize(450, 340));
		frame->Show(true);
		return true;
	}
};

#ifndef _DEBUG
	wxIMPLEMENT_APP(App);
#else
	wxIMPLEMENT_APP_CONSOLE(App);
#endif
