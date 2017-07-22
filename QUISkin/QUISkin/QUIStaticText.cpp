#include"stdafx.h"
#include"QUIStaticText.h"

CQUIStaticText::CQUIStaticText()
{
	memset(&m_rcText, 0, sizeof(RECT));
}

CQUIStaticText::~CQUIStaticText()
{

}
void CQUIStaticText::SetAlign(UINT uAStyle)
{
	m_uAlign = uAStyle;
}
void CQUIStaticText::SetVlign(UINT uVStyle)
{
	m_uVlign = uVStyle;
}
void CQUIStaticText::SetLightColor(DWORD dwColor)
{
	m_dwLightColor = dwColor;
}
void CQUIStaticText::DrawText(Gdiplus::Graphics& grx)
{
	//1.绘制之前背景设置透明
	HDC hdc = grx.GetHDC();
	::SetBkMode(hdc, TRANSPARENT);
	//通过GDI+ GetHDC获取到hdc，必须要释放
	grx.ReleaseHDC(hdc);

	//创建字体
	Gdiplus::FontFamily family(m_strFont.c_str());
	Gdiplus::Font font(&family, m_dwFontSize);

	//对齐格式
	Gdiplus::StringFormat format;
	format.SetAlignment((Gdiplus::StringAlignment)m_uAlign);
	format.SetLineAlignment((Gdiplus::StringAlignment)m_uVlign);
	//创建画刷
	Gdiplus::SolidBrush brush(Gdiplus::Color(GetRValue(m_dwTextColor), GetGValue(m_dwTextColor), GetBValue(m_dwTextColor)));
	//兼容高亮和不高亮显示两种风格
	if (m_bLightColor&&m_dwLightColor != 0)
		brush.SetColor(Gdiplus::Color(GetRValue(m_dwLightColor), GetGValue(m_dwLightColor), GetBValue(m_dwLightColor)));
	//绘制文本
	grx.DrawString(m_strCaption.c_str(), m_strCaption.length(), &font, Gdiplus::RectF(m_bound.left, m_bound.top, m_bound.right - m_bound.left, m_bound.bottom - m_bound.top), &format, &brush);

	//只计算一次文本区域
	//if (m_rcText.right - m_rcText.left <= 0)
	{//计算文本区域
		Gdiplus::RectF rcTxt;
		grx.MeasureString(m_strCaption.c_str(), m_strCaption.length(), &font,
			Gdiplus::RectF(m_bound.left, m_bound.top, m_bound.right - m_bound.left, m_bound.bottom - m_bound.top),
			&format, &rcTxt);
		m_rcText.left = rcTxt.GetLeft();
		m_rcText.top = rcTxt.GetTop();
		m_rcText.right = rcTxt.GetRight();
		m_rcText.bottom = rcTxt.GetBottom();
	}

}
LRESULT CQUIStaticText::OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	__super::OnControlMessage(message, wParam, lParam);

	switch (message)
	{
		case WM_LBUTTONDOWN:
		{//鼠标左键按下在我的地盘,把这个按下事件要过滤掉
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			if (HitTest(pt))
				return S_OK;
		}
		break;
		case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			
			if (HitTest(pt))
			{//判断鼠标是否落在我们区域
				if (!m_bLightColor)
				{
					m_bLightColor = TRUE;
					InvalidBounds();
				}
				return S_OK;
			}
			else
			{
				if (m_bLightColor)
				{//如果当前是高亮显示，那么要恢复文本颜色
					m_bLightColor = FALSE;
					InvalidBounds();
					return S_OK;
				}
			}
		}
		break;
	}
	return S_FALSE;
}
BOOL CQUIStaticText::HitTest(POINT pt)
{
	if (!IsVisible())
		return FALSE;
	//不在区域范围
	if (PtInRect(&m_rcText, pt))
		return TRUE;

	return FALSE;
}