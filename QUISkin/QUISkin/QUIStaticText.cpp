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
	//1.����֮ǰ��������͸��
	HDC hdc = grx.GetHDC();
	::SetBkMode(hdc, TRANSPARENT);
	//ͨ��GDI+ GetHDC��ȡ��hdc������Ҫ�ͷ�
	grx.ReleaseHDC(hdc);

	//��������
	Gdiplus::FontFamily family(m_strFont.c_str());
	Gdiplus::Font font(&family, m_dwFontSize);

	//�����ʽ
	Gdiplus::StringFormat format;
	format.SetAlignment((Gdiplus::StringAlignment)m_uAlign);
	format.SetLineAlignment((Gdiplus::StringAlignment)m_uVlign);
	//������ˢ
	Gdiplus::SolidBrush brush(Gdiplus::Color(GetRValue(m_dwTextColor), GetGValue(m_dwTextColor), GetBValue(m_dwTextColor)));
	//���ݸ����Ͳ�������ʾ���ַ��
	if (m_bLightColor&&m_dwLightColor != 0)
		brush.SetColor(Gdiplus::Color(GetRValue(m_dwLightColor), GetGValue(m_dwLightColor), GetBValue(m_dwLightColor)));
	//�����ı�
	grx.DrawString(m_strCaption.c_str(), m_strCaption.length(), &font, Gdiplus::RectF(m_bound.left, m_bound.top, m_bound.right - m_bound.left, m_bound.bottom - m_bound.top), &format, &brush);

	//ֻ����һ���ı�����
	//if (m_rcText.right - m_rcText.left <= 0)
	{//�����ı�����
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
		{//�������������ҵĵ���,����������¼�Ҫ���˵�
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
			{//�ж�����Ƿ�������������
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
				{//�����ǰ�Ǹ�����ʾ����ôҪ�ָ��ı���ɫ
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
	//��������Χ
	if (PtInRect(&m_rcText, pt))
		return TRUE;

	return FALSE;
}