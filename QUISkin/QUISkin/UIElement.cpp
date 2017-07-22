#include"stdafx.h"
#include"UIElement.h"


CUIElement::CUIElement()
{
	m_dwBackColor = 0;
	m_dwBackColor = 0;
	m_pCallBack = NULL;
	m_bVisible = TRUE;
	m_dwFontSize = 10;
	m_strFont = L"楷体";
}

CUIElement::~CUIElement()
{

}

void CUIElement::Create(const TCHAR* szEleID, const RECT& rc, HWND hHostWnd, IQUIEventCallBack* pCallBack)
{
	m_hHostWnd = hHostWnd;
	m_pCallBack = pCallBack;
	if (szEleID)
		m_strID = szEleID;
	m_bound = rc;
}

void CUIElement::SetCaption(const TCHAR* szCaption)
{
	if (szCaption)
	{
		m_strCaption = szCaption;
	}
}
const TCHAR*CUIElement::GetCaption()
{
	return m_strCaption.c_str();
}
void CUIElement::SetBound(const RECT& rc)
{
	m_bound = rc;
}
void CUIElement::GetBound(RECT* lpRect)
{
	if (lpRect)
		*lpRect = m_bound;
}
void CUIElement::SetID(const TCHAR* szID)
{
	if (szID)
		m_strID = szID;
}
const TCHAR* CUIElement::GetID()
{
	return m_strID.c_str();
}
void CUIElement::SetVisible(BOOL bVisible)
{
	m_bVisible = bVisible;
}
void CUIElement::SetEnable(BOOL bEnable)
{
	m_bEnable = bEnable;
}
void CUIElement::SetBackColor(DWORD dwColor)
{
	m_dwBackColor = dwColor;
}
void CUIElement::SetToolText(const TCHAR* szToolText)
{
	if (szToolText)
		m_strToolTips = szToolText;
}
void CUIElement::SetBorderSize(DWORD dwBorderSize)
{
	m_dwBorder = dwBorderSize;
}
void CUIElement::SetBorderColor(DWORD dwBorderColor)
{
	m_dwBorderColor = dwBorderColor;
}
void CUIElement::SetBgImage(const TCHAR* szImage)
{
	if (szImage)
		m_strBgImage = szImage;
}
void CUIElement::SetHostWnd(HWND hWnd)
{
	m_hHostWnd = hWnd;
}
HWND CUIElement::GetHostWnd()
{
	return m_hHostWnd;
}
void CUIElement::InvalidBounds()
{
	::InvalidateRect(m_hHostWnd, &m_bound, FALSE);
}
BOOL CUIElement::HitTest(POINT pt)
{
	if (PtInRect(&m_bound, pt))
		return TRUE;

	return FALSE;
}
BOOL CUIElement::IsVisible()
{
	//1.直接隐藏了
	if (!m_bVisible)
		return FALSE;
	//2.元素不在窗口可见范围内
	RECT rcParent;
	::GetClientRect(m_hHostWnd, &rcParent);
	RECT rcVisible;
	::IntersectRect(&rcVisible, &m_bound, &rcParent);//求两个矩形的交集

	if (::IsRectEmpty(&rcVisible))
		return FALSE;

	//3.元素尺寸等于0
	if (m_bound.right - m_bound.left <= 0 || m_bound.bottom - m_bound.top <= 0)
		return FALSE;

	return TRUE;
}
void CUIElement::DrawBkColor(Gdiplus::Graphics& grx)
{
	if (m_dwBackColor)
	{
		Gdiplus::SolidBrush hbr(Gdiplus::Color(255, GetRValue(m_dwBackColor), GetGValue(m_dwBackColor), GetBValue(m_dwBackColor)));
		grx.FillRectangle(&hbr, Gdiplus::Rect(m_bound.left, m_bound.top, m_bound.right - m_bound.left, m_bound.bottom - m_bound.top));
	}
}
void CUIElement::DrawBkImage(Gdiplus::Graphics& grx)
{
	if (m_strBgImage.length() <= 0)
		return;
	Gdiplus::Image im(m_strBgImage.c_str());

	grx.DrawImage(&im, Gdiplus::Rect(m_bound.left, m_bound.top, m_bound.right - m_bound.left, m_bound.bottom - m_bound.top));
}
void CUIElement::DrawStatusImage(Gdiplus::Graphics& grx)
{
	//留给子类重写
}
void CUIElement::DrawText(Gdiplus::Graphics& grx)
{
	if (m_strCaption.length())
	{
		//字体背景透明
		HDC hdc = grx.GetHDC();
		::SetBkMode(hdc, TRANSPARENT);
		grx.ReleaseHDC(hdc);
		Gdiplus::SolidBrush hbr(Gdiplus::Color(255, (BYTE)m_dwTextColor >> 16, (BYTE)m_dwTextColor >> 8, BYTE(m_dwTextColor)));
		Gdiplus::FontFamily family(m_strFont.c_str());
		Gdiplus::Font font(&family, m_dwFontSize);

		Gdiplus::Status stat = grx.DrawString(m_strCaption.c_str(), m_strCaption.length(), &font,
			Gdiplus::PointF(m_bound.left, m_bound.top), &hbr);
		if (stat != Gdiplus::Ok)
			int i = 0;
	}
}
void CUIElement::DrawBorder(Gdiplus::Graphics& grx)
{
	if (m_dwBorder != 0)
	{
		Gdiplus::Pen pen(Gdiplus::Color(255, GetRValue(m_dwBorderColor), GetGValue(m_dwBorderColor), GetBValue(m_dwBorderColor)), m_dwBorder);
		grx.DrawRectangle(&pen, Gdiplus::Rect(m_bound.left, m_bound.top, m_bound.right - m_bound.left, m_bound.bottom - m_bound.top));
	}
}
void CUIElement::DoPaint(Gdiplus::Graphics& grx)
{
	//判断是否可见
	if (!IsVisible())
		return;

	//1.绘制背景颜色
	DrawBkColor(grx);
	//2.绘制背景图
	DrawBkImage(grx);
	//3.绘制状态图
	DrawStatusImage(grx);
	//4.绘制文本
	DrawText(grx);
	//5.绘制边框
	DrawBorder(grx);
}
LRESULT CUIElement::OnControlMessage(UINT message,WPARAM wParam, LPARAM lParam)
{
	return S_FALSE;
}

void CUIElement::SetFontSize(DWORD dwFontSize)
{
	m_dwFontSize = dwFontSize;
}
void CUIElement::SetFamily(const TCHAR* szFamily)
{
	if (szFamily)
		m_strFont = szFamily;
}
void CUIElement::SetTextColor(DWORD dwTxtColor)
{
	m_dwTextColor = dwTxtColor;
}