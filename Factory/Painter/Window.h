#pragma once
#include <Windows.h>

class Window
{
public:
	Window();

	HWND GetHandle();
	bool IsOpen()const;
	bool PeekAndProcessEvent();

private:
	static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	MSG m_msg;
};
