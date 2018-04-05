#include "MainFrm.h"

MainFrm::MainFrm(PictureDraft& draft)
	: m_draft(draft)
	, m_canvas(nullptr)
{
	RECT rect = { 0, 0, 1280, 1024 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, TRUE, WS_EX_OVERLAPPEDWINDOW);
	Create(NULL, _T("Windows Application Tester"), WS_OVERLAPPEDWINDOW,
		CRect(0, 0, rect.right - rect.left, rect.bottom - rect.top), NULL);
	m_canvas.reset(new D2DCanvas(m_hWnd));
}

MainFrm::~MainFrm()
{
}

void MainFrm::OnFileExit()
{
	if (!DestroyWindow())
	{
		MessageBox(_T("can't close window right now"));
	}
}

void MainFrm::OnHelpAbout()
{
	MessageBox(_T("Usage: Painter.exe\n"
		"All shapes must be listed in file 'input.txt'\n"
		"Every shape must be delimited by newline character\n"
		"List of available shapes: (every point is two numbers)\n"
		"Triangle <point1> <point2> <point3> <color>\n"
		"Rectangle <left top point> <right bottom point> <color>\n"
		"Ellipse <center point> <horizontal radius> <vertical radius> <color>\n"
		"RegularPolygon <center point> <radius> <vertex count> <color>\n"
		"Colors can be written in hex format like 'ff00ff'\n"
		"If wanted color is in above list, it can be written by word\n"
		"[green, red, blue, yellow, pink, black]\n"
		"Example: Rectangle 10 10 100 100 red\\nTriangle 10 10 30 30 50 10 ff00ff"));
}

int MainFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) != 0)
	{
		MessageBox(_T("Failed to create window..."));
		return -1;
	}
	if (m_menu.LoadMenu(IDR_MENU1))
	{
		SetMenu(&m_menu);
		return 0;
	}
	return -1;
}

void MainFrm::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
}

void MainFrm::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);

	switch (nState)
	{
	case WA_ACTIVE:
		SetWindowText(_T("This window has been activated, without the mouse!"));
		break;
	case WA_INACTIVE:
		SetWindowText(_T("This window has been deactivated and cannot be changed now!!"));
		break;
	case WA_CLICKACTIVE:
		SetWindowText(_T("This window has been activated using the mouse!!!"));
		break;
	}
}

void MainFrm::OnPaint()
{
	CPaintDC dc(this);
	(void)dc;

	m_canvas->BeginDraw();
	m_canvas->Clear(Color{255, 255, 255});

	auto painter = std::make_unique<Painter>();
	painter->DrawPicture(m_draft, *m_canvas);

	m_canvas->EndDraw();
}

void MainFrm::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	if (m_canvas)
	{
		m_canvas->Resize(cx, cy);
	}
}

void MainFrm::OnSizing(UINT nType, LPRECT lpRect)
{
	CFrameWnd::OnSizing(nType, lpRect);
	SetWindowText(_T("Resized"));
}

void MainFrm::OnMove(int x, int y)
{
	CFrameWnd::OnMove(x, y);
}

void MainFrm::OnMoving(UINT nSide, LPRECT lpRect)
{
	CFrameWnd::OnMoving(nSide, lpRect);
	SetWindowText(_T("Moving"));
}

void MainFrm::OnClose()
{
	CFrameWnd::OnClose();
}

void MainFrm::OnDestroy()
{
	CFrameWnd::OnDestroy();
}

void MainFrm::OnLButtonUp(UINT nFlags, CPoint point)
{
	CFrameWnd::OnLButtonUp(nFlags, point);
}

BEGIN_MESSAGE_MAP(MainFrm, CFrameWnd)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_ACTIVATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_MOVE()
	ON_WM_MOVING()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()
