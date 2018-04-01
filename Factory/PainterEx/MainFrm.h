#pragma once
#define _WIN32_WINNT _WIN32_WINNT_VISTA
#include <afxwin.h>
#include "resource.h"

#include <memory>
#include "D2DCanvas.h"

#include "../libpainter/ShapeFactory.h"
#include "../libpainter/Designer.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/Painter.h"

class MainFrm : public CFrameWnd
{
public:
	MainFrm(PictureDraft& draft);
	~MainFrm();

private:
	std::unique_ptr<D2DCanvas> m_canvas;
	PictureDraft & m_draft;

	CMenu m_menu;

	void OnFileExit();
	void OnHelpAbout();
	int OnCreate(LPCREATESTRUCT);
	void OnShowWindow(BOOL, UINT);
	void OnActivate(UINT, CWnd*, BOOL);
	void OnPaint();
	void OnSize(UINT, int, int);
	void OnSizing(UINT, LPRECT);
	void OnMove(int, int);
	void OnMoving(UINT, LPRECT);
	void OnClose();
	void OnDestroy();
	void OnLButtonUp(UINT, CPoint);

	DECLARE_MESSAGE_MAP()
};
