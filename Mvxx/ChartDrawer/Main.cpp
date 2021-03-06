#include "stdafx.h"
#include "MainFrame.h"
#include "HarmonicsCollection.h"
#include "HarmonicsController.h"

namespace
{
const wxSize MAIN_FRAME_SIZE = { 920, 720 };
const wxString MAIN_FRAME_TITLE = "ChartDrawer";

class GdiplusInitializer
{
public:
	GdiplusInitializer()
	{
		Gdiplus::Status status = Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, nullptr);
		assert(status == Gdiplus::Status::Ok);
		(void)status;
	}

	~GdiplusInitializer()
	{
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
	}

private:
	Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_gdiplusToken;
};
}

class MyApp : public wxApp
{
public:
	bool OnInit() wxOVERRIDE
	{
		m_frame = new MainFrame(MAIN_FRAME_TITLE, MAIN_FRAME_SIZE);
		m_harmonics = std::make_shared<HarmonicsCollection>();
		m_controller = std::make_unique<HarmonicsController>(
			m_harmonics,
			m_frame->GetMainPanel()->GetSelectionView(),
			m_frame->GetMainPanel()->GetPropertiesView(),
			m_frame->GetMainPanel()->GetCanvasView(),
			m_frame->GetMainPanel()->GetTableView());
		m_frame->Show(true);
		m_frame->Centre();
		m_frame->GetMainPanel()->GetCanvasView()->UpdateDrawingAreaSize();
		return true;
	}

private:
	MainFrame* m_frame;
	std::shared_ptr<HarmonicsCollection> m_harmonics;
	std::unique_ptr<HarmonicsController> m_controller;
	GdiplusInitializer m_gdiplus;
};

#ifndef _DEBUG
	wxIMPLEMENT_APP(MyApp);
#else
	wxIMPLEMENT_APP_CONSOLE(MyApp);
#endif
