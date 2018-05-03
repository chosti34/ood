#include "stdafx.h"
#include "MainFrm.h"
#include "DrawingPanel.h"

class App : public wxApp
{
public:
	bool OnInit()wxOVERRIDE
	{
		wxFrame* frame = new MainFrm("Slides");
		wxPanel* panel = new DrawingPanel(frame);

		frame->SetClientSize(wxRect(0, 0, 800, 600));
		frame->Centre();
		frame->Show(true);

		return true;
	}
};

#ifndef _DEBUG
	wxIMPLEMENT_APP(App);
#else
	wxIMPLEMENT_APP_CONSOLE(App);
#endif
