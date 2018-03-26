#include "stdafx.h"
#include "Window.h"
#include <stdexcept>

Window::Window()
	: m_hWnd(nullptr)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hbrBackground = HBRUSH(COLOR_WINDOW);
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.lpfnWndProc = &WndProc;
	wcex.lpszClassName = L"WindowClass";
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		throw std::runtime_error("failed to register window class");
	}

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);

	m_hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		L"WindowClass",
		L"Painter",
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL, GetModuleHandle(nullptr), NULL);

	if (!m_hWnd)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		throw std::runtime_error("failed to create window");
	}

	m_msg.message = WM_NULL;
	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
}

HWND Window::GetHandle()
{
	return m_hWnd;
}

bool Window::IsOpen()const
{
	return m_msg.message != WM_QUIT;
}

bool Window::PeekAndProcessEvent()
{
	if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
	{
		DispatchMessage(&m_msg);
		return true;
	}
	return false;
}

LRESULT Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
