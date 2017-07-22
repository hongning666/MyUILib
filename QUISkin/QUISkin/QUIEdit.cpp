#include"stdafx.h"
#include"QUIEdit.h"
#include<windowsx.h>
#include<commctrl.h>

CQUIEdit::CQUIEdit()
{
	m_dwStyle = WS_CHILD | WS_VISIBLE;
	m_pOldWndProc = NULL;
	m_eState = E_EditState_Normal;
}

CQUIEdit::~CQUIEdit()
{

}

void CQUIEdit::SetState(enEditState eState)
{
	m_eState = eState;
	InvalidBounds();
}
void CQUIEdit::SetLightColor(DWORD dwLightColor1, DWORD dwLightColor2)
{
	m_dwLightColor1 = dwLightColor1;
	m_dwLightColor2 = dwLightColor2;
	if (m_hWnd&&m_eState != E_EditState_Normal)
	{
		InvalidBounds();
	}
}
void CQUIEdit::DrawBorder(Gdiplus::Graphics& grx)
{
	Gdiplus::Color clr(GetRValue(m_dwBorderColor), GetGValue(m_dwBorderColor), GetBValue(m_dwBorderColor));
	if (m_eState == E_EditState_Over)
		clr.SetFromCOLORREF(m_dwLightColor1);
	else if (m_eState == E_EditState__Focus)
		clr.SetFromCOLORREF(m_dwLightColor2);

	Gdiplus::Pen pen(clr, m_dwBorder);
	pen.SetAlignment(Gdiplus::PenAlignmentInset);
	grx.DrawRectangle(&pen, m_bound.left, m_bound.top, m_bound.right - m_bound.left, m_bound.bottom - m_bound.top);
}

void CQUIEdit::SetStyle(DWORD dwStyle)
{
	m_dwStyle = dwStyle;
}
BOOL CQUIEdit::Create(const TCHAR* szEleID, const RECT& rc, HWND hWndParent, HINSTANCE hInst, IQUIEventCallBack* pCallBack)
{
	//1.创建元素
	CUIElement::Create(szEleID, rc, hWndParent, pCallBack);
	//2.创建窗口
	RECT rcWnd;
	rcWnd.left = rc.left + m_dwBorder;
	rcWnd.top = rc.top + m_dwBorder;
	rcWnd.right = rc.right - m_dwBorder;
	rcWnd.bottom = rc.bottom - m_dwBorder;
	if (!CQUIWnd::Create(hWndParent, L"", rcWnd, m_dwStyle, hInst))
		return FALSE;

	//怎么设置字体
	HFONT hFont = (HFONT)GetStockFont(DEFAULT_GUI_FONT);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)hFont, 1);






	//3.设置自己的窗口过程
	SetWindowLongPtr(m_hWnd, GWL_USERDATA, (LONG)this);
	SetWindowLongPtr(m_hWnd, GWL_WNDPROC, (LONG)OnControlProc);



	return TRUE;
}
LRESULT CALLBACK CQUIEdit::OnControlProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CQUIEdit* pThis = (CQUIEdit*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	return pThis->HandleMessage(message, wParam, lParam);
}
BOOL CQUIEdit::RegisterWndClass()
{
	WNDCLASSEX wc = { 0 };
	//获取已经注册的EDIT窗口
	if (!GetClassInfoEx(NULL, GetWndClassName(), &wc))
		return FALSE;

	m_pOldWndProc = wc.lpfnWndProc;//保存edit默认的窗口过程

	return TRUE;
}
LPCTSTR CQUIEdit::GetWndClassName()
{
	return WC_EDIT;
}
LRESULT CQUIEdit::HandleMessage(UINT message, WPARAM wparam, LPARAM lparam)
{
	//调用默认的窗口过程
	switch (message)
	{
		case WM_SETFOCUS:
		{
			SetState(E_EditState__Focus);
		}
			break;
		case WM_KILLFOCUS:
		{
			SetState(E_EditState_Normal);
		}
			break;
	}
	return CallWindowProc(m_pOldWndProc, m_hWnd, message, wparam, lparam);
}
LRESULT CQUIEdit::OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	CUIElement::OnControlMessage(message, wParam, lParam);
	switch (message)
	{
		case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			if (HitTest(pt))
			{
				if (m_eState == E_EditState_Normal)
					SetState(E_EditState_Over);
				return S_OK;
			}
			else
			{
				if (m_eState == E_EditState_Over)
				{
					SetState(E_EditState_Normal);
					return S_OK;
				}
			}
		}
			break;
	}
	return S_FALSE;
}