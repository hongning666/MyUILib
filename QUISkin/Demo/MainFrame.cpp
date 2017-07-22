#include "stdafx.h"
#include "MainFrame.h"


CMainFrame::CMainFrame()
{
}


CMainFrame::~CMainFrame()
{
}

LPCTSTR CMainFrame::GetWndClassName()
{
	return L"XUIMainFrame";
}

void CMainFrame::OnDestoryWindow(WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
}

void CMainFrame::OnCreate(WPARAM wParam, LPARAM lParam)
{
	RECT rcWnd;
	GetClientRect(&rcWnd);
	RECT rc;
	rc.left = 10;
	rc.top = 32;
	rc.right = rcWnd.right-20;
	rc.bottom = rcWnd.bottom-10;
	
	m_List.Create(L"IDC_LIST", rc, m_hWnd, this);
	m_List.SetBackColor(RGB(255, 255, 255));
	m_List.SetBorderColor(RGB(0, 0, 255));
	m_List.SetBorderSize(1);
	m_List.InitColunm(32, RGB(0xa2, 0xa2, 0xa2));
	m_List.InsertColunm(0, L"姓名", 100, NULL);
	m_List.InsertColunm(1, L"电话", 100, NULL);
	m_List.InsertColunm(2, L"地址", 200, NULL);
	m_List.SetItemBackColor(RGB(230, 0, 255), RGB(255, 111, 0));
	m_List.SetItemHeight(32, 36);
	m_List.SetTextColor(RGB(0, 255, 0));
	m_List.SetVScrollImage(L"E:\\win32\\QUISkin\\Bin\\Debug\\Skin\\Image\\Pub_vsrcoll.png");

	for (int i = 0; i < 30; i++)
	{
		TCHAR szName[20] = { 0 };
		wsprintf(szName, L"Text%d", i);
		m_List.InsertItem(i, szName);
		m_List.SetItemText(i, 1, L"1806632312");
		m_List.SetItemText(i, 2, L"美国");
	}

	m_BtnClose.SetStateImage(L"G:\\Window_btn_close.png", 5);
	rc.left = rcWnd.right - 23;
	rc.top = 5;
	rc.right = rc.left + 18;
	rc.bottom = rc.top + 18;
	m_BtnClose.Create(L"IDC_CLOSE", rc, m_hWnd, this);
}

void CMainFrame::OnPaint(WPARAM wParam, LPARAM lParam)
{
	__super::OnPaint(wParam, lParam);
	/*PAINTSTRUCT pcs;
	HDC hdc = BeginPaint(m_hWnd, &pcs);

	RECT rc;
	GetClientRect(&rc);

	::FillRect(hdc, &rc, CreateSolidBrush(RGB(0, 0, 255)));

	::EndPaint(m_hWnd, &pcs);*/
}

void CMainFrame::OnSize(WPARAM wParam, LPARAM lParam)
{
	/*RECT rcClient;
	GetClientRect(m_hWnd, &rcClient);

	rcClient.right -= 20;
	rcClient.bottom -= 20;

	m_Child.MoveWindow(rcClient, TRUE);*/
}

void CMainFrame::OnNotifyCmd(CUIElement* pElement)
{
	StdString strID = pElement->GetID();
	if (strID.compare(m_BtnClose.GetID()) == 0)
	{
		PostMessage(m_hWnd, WM_CLOSE, 0, 0);
		return;
	}

	//判断按下了哪个按钮
	StdString strCaption = pElement->GetCaption();
	MessageBox(m_hWnd, strCaption.c_str(), L"点击事件", MB_OK);
}

void CMainFrame::OnPaintControl(Gdiplus::Graphics& grx)
{
	m_List.DoPaint(grx);
	m_BtnClose.DoPaint(grx);
}

LRESULT CMainFrame::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_List.OnControlMessage(message, wParam, lParam) == S_OK)
		return S_OK;
	if (m_BtnClose.OnControlMessage(message, wParam, lParam) == S_OK)
		return S_OK;
	return __super::HandleMessage(message, wParam, lParam);
}
