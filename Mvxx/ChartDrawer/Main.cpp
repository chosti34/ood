#include "stdafx.h"
#include "MainFrame.h"
#include "Harmonics.h"
#include "Controller.h"

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
		m_frame = new MainFrame(MAIN_FRAME_TITLE, MAIN_FRAME_SIZE);
		m_frame->Show(true);
		m_controller = std::make_unique<Controller>(m_frame, m_harmonics);
		return true;
	}

private:
	MainFrame* m_frame;
	std::shared_ptr<Harmonics> m_harmonics;
	std::unique_ptr<Controller> m_controller;
};

#ifndef _DEBUG
	wxIMPLEMENT_APP(MyApp);
#else
	wxIMPLEMENT_APP_CONSOLE(MyApp);
#endif
