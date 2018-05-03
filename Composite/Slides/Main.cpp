#include "stdafx.h"
#include "MainFrm.h"
#include "DrawingPanel.h"

namespace
{
class GdiplusInitializer
{
public:
	GdiplusInitializer()
	{
		Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, nullptr);
	}

	~GdiplusInitializer()
	{
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
	}

private:
	Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_gdiplusToken;
};

class App : public wxApp
{
public:
	bool OnInit()wxOVERRIDE
	{
		GdiplusInitializer gdiplus;

		MainFrm* frame = new MainFrm("Slides");
		DrawingPanel* panel = new DrawingPanel(frame);

		frame->SetClientSize(wxRect(0, 0, 800, 600));
		frame->Centre();
		frame->Show();

		return true;
	}
};
}

#ifndef _DEBUG
	wxIMPLEMENT_APP(App);
#else
	wxIMPLEMENT_APP_CONSOLE(App);
#endif
