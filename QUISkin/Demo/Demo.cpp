// Demo.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Demo.h"
#include "MainFrame.h"
#include <gdiplus.h>
#define MAX_LOADSTRING 100

CMainFrame g_MainFrame;
// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

Gdiplus::GdiplusStartupInput g_Gdiplus;
ULONG_PTR g_GdiToken = 0;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// TODO:  �ڴ˷��ô��롣
	GdiplusStartup(&g_GdiToken, &g_Gdiplus, NULL);
	RECT rcDrag;
	rcDrag.left = 0;
	rcDrag.right = 500;
	rcDrag.top = 0;
	rcDrag.bottom = 100;
	g_MainFrame.SetDragRect(rcDrag);

	RECT rc;
	rc.left = 800;
	rc.top = 500;
	rc.right = 1300;
	rc.bottom = 900;
	
	g_MainFrame.SetBground(L"G:\\main.png");
	

	g_MainFrame.Create(NULL, L"QUISkin", rc, WS_POPUP, hInstance);
	g_MainFrame.ShowWindow(SW_SHOW);
	g_MainFrame.UpdateWindow();

	MSG msg;
	// ����Ϣѭ��: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, NULL, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	Gdiplus::GdiplusShutdown(g_GdiToken);
	return (int)msg.wParam;
}


