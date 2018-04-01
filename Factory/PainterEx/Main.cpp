#include "MainFrm.h"
#include <fstream>

class MyApp : public CWinApp
{
private:
	PictureDraft m_draft;
	MainFrm* m_frm;

	BOOL InitInstance()
	{
		auto factory = std::make_unique<ShapeFactory>();
		auto designer = std::make_unique<Designer>(*factory);

		std::ifstream file("input.txt");
		m_draft = designer->CreateDraft(file);

		m_frm = new MainFrm(m_draft);
		m_pMainWnd = m_frm;
		m_frm->ShowWindow(SW_NORMAL);
		m_frm->CenterWindow();
		m_frm->UpdateWindow();
		return TRUE;
	}
};

MyApp app;
