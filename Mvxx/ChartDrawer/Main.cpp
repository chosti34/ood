#include "stdafx.h"
#include "MainFrame.h"
#include "HarmonicsCollection.h"
#include "HarmonicsController.h"

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
		m_harmonics = std::make_shared<HarmonicsCollection>();
		m_controller = std::make_unique<HarmonicsController>(m_frame, m_harmonics);
		m_frame->Show(true);
		return true;
	}

private:
	MainFrame* m_frame;
	std::shared_ptr<HarmonicsCollection> m_harmonics;
	std::unique_ptr<HarmonicsController> m_controller;
};

#ifndef _DEBUG
	wxIMPLEMENT_APP(MyApp);
#else
	wxIMPLEMENT_APP_CONSOLE(MyApp);
#endif
