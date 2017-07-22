#include"stdafx.h"
#include"QUIScrollBar.h"


CQUIScrollBar::CQUIScrollBar(IScrollbarCallback* pCallback)
:m_pCallBack(pCallback)
{
	m_eBarStyle = E_ScrollBar_VBar;
	m_eState = E_ScrollBarState_Normal;
	m_bVisible = FALSE;
	m_iRang = 0;
	m_iScrollPos = 0;
	m_bThumPress = FALSE;
}
CQUIScrollBar::~CQUIScrollBar()
{

}

void CQUIScrollBar::SetScrollBarStyle(enScrollBarStyle eBarStyle)
{
	m_eBarStyle = eBarStyle;
}
enScrollBarStyle CQUIScrollBar::GetScrollBar()
{
	return m_eBarStyle;
}
void CQUIScrollBar::SetStateImage(const TCHAR* szImage)
{
	m_strStateImage = szImage;
}
void CQUIScrollBar::SetState(enScrollBarState eState)
{
	m_eState = eState;
}
enScrollBarState CQUIScrollBar::GetState()
{
	return m_eState;
}
void CQUIScrollBar::DrawStatusImage(Gdiplus::Graphics& grx)
{

	//横向滚动条
	if (m_eBarStyle == E_ScrollBar_HBar)
	{
		DrawHScroll(grx);
	}
	else
	{//竖向滚动条
		DrawVScroll(grx);
	}
}
void CQUIScrollBar::DrawHScroll(Gdiplus::Graphics& grx)
{
	Gdiplus::Image im(m_strStateImage.c_str());
	//1.先绘制背景
	int iLeft = im.GetWidth()/4*2;
	int iTop = (m_eState - 1)*im.GetHeight() / 4;
	grx.DrawImage(&im, Gdiplus::RectF(m_bound.left, m_bound.top, m_bound.right - m_bound.left, m_bound.bottom - m_bound.top),
		iLeft, iTop, im.GetWidth() / 4, im.GetHeight() / 4, Gdiplus::UnitPixel);
	//2.左边按钮
	iLeft = 0;
	grx.DrawImage(&im, Gdiplus::RectF(m_bound.left, m_bound.top, m_bound.bottom - m_bound.top, m_bound.bottom - m_bound.top),
		iLeft, iTop, im.GetWidth() / 4, im.GetHeight() / 4, Gdiplus::UnitPixel);
	//3.右边按钮
	iLeft = im.GetWidth() / 4;
	grx.DrawImage(&im, Gdiplus::RectF(m_bound.right-m_bound.bottom+m_bound.top, m_bound.top, m_bound.bottom - m_bound.top, m_bound.bottom - m_bound.top),
		iLeft, iTop, im.GetWidth() / 4, im.GetHeight() / 4, Gdiplus::UnitPixel);
	//4.画滑块
	if (m_iRang <= 0)
		return;
	iLeft = im.GetWidth() / 4 * 3;
	//滑块在窗口上面的左边实际坐标
	int iThumLeft = GetThumLeft();
	grx.DrawImage(&im, Gdiplus::RectF(iThumLeft, m_bound.top, m_bound.bottom - m_bound.top, m_bound.bottom - m_bound.top),
		iLeft, iTop, im.GetWidth() / 4, im.GetHeight() / 4, Gdiplus::UnitPixel);
}
int CQUIScrollBar::GetThumLeft()
{
	int iThumLeft = 0;
	double dbRate = (double)m_iScrollPos / (double)m_iRang;//百分比
	if (m_eBarStyle == E_ScrollBar_HBar)
	{//横向滚动条
		int iWidth = m_bound.right - m_bound.left - (m_bound.bottom - m_bound.top) * 3;
		iThumLeft = m_bound.left + dbRate*iWidth + (m_bound.bottom - m_bound.top);
	}
	else
	{//竖向滚动条
		//计算滑块的y轴坐标
		int iHeight = m_bound.bottom - m_bound.top - (m_bound.right - m_bound.left) * 3;
		iThumLeft = m_bound.top + (m_bound.right - m_bound.left) + dbRate*iHeight;
	}
	return iThumLeft;
}
void CQUIScrollBar::GetThumRect( RECT& rcThum)
{
	if (m_eBarStyle == E_ScrollBar_VBar)
	{
		rcThum.left = m_bound.left;
		rcThum.top = GetThumLeft();
		rcThum.right = rcThum.left + (m_bound.right - m_bound.left);
		rcThum.bottom = rcThum.top + (m_bound.right - m_bound.left);
	}
	else
	{
		rcThum.left = GetThumLeft();
		rcThum.top = m_bound.top;
		rcThum.right = rcThum.left + (m_bound.bottom - m_bound.top);
		rcThum.bottom = rcThum.top + (m_bound.bottom - m_bound.top);
	}
}
void CQUIScrollBar::GetLeftBtnRect(RECT& rcBtn)
{
	if (m_eBarStyle == E_ScrollBar_HBar)
	{
		rcBtn.left = m_bound.left;
		rcBtn.top = m_bound.top;
		rcBtn.right = rcBtn.left + (m_bound.bottom - m_bound.top);
		rcBtn.bottom = rcBtn.top + (m_bound.bottom - m_bound.top);
	}
	else
	{
		rcBtn.left = m_bound.left;
		rcBtn.top = m_bound.top;
		rcBtn.right = rcBtn.left + (m_bound.right - m_bound.left);
		rcBtn.bottom = rcBtn.top + (m_bound.right - m_bound.left);
	}
}
void CQUIScrollBar::GetRightBtnRect(RECT& rcBtn)
{
	if (m_eBarStyle == E_ScrollBar_HBar)
	{
		rcBtn.left = m_bound.right - (m_bound.bottom - m_bound.top);
		rcBtn.top = m_bound.top;
		rcBtn.right = rcBtn.left + (m_bound.bottom - m_bound.top);
		rcBtn.bottom = rcBtn.top + (m_bound.bottom - m_bound.top);
	}
	else
	{
		rcBtn.left = m_bound.left;
		rcBtn.top = m_bound.bottom - (m_bound.right - m_bound.left);
		rcBtn.right = m_bound.right;
		rcBtn.bottom = m_bound.bottom;
	}
}
void CQUIScrollBar::DrawVScroll(Gdiplus::Graphics& grx)
{
	//1.绘制背景
	Gdiplus::Image im(m_strStateImage.c_str());
	int iLeft = im.GetWidth() / 4 * (m_eState - 1);
	int iTop = im.GetHeight() / 2;
	grx.DrawImage(&im, Gdiplus::RectF(m_bound.left, m_bound.top, m_bound.right - m_bound.left, m_bound.bottom - m_bound.top), iLeft, iTop, im.GetWidth() / 4, im.GetHeight() / 4, Gdiplus::UnitPixel);
	//2.向上的箭头按钮
	iTop = 0;
	grx.DrawImage(&im, Gdiplus::RectF(m_bound.left, m_bound.top, m_bound.right - m_bound.left, m_bound.right - m_bound.left),iLeft, iTop, im.GetWidth() / 4, im.GetHeight() / 4, Gdiplus::UnitPixel);
	//3.向下的箭头按钮
	iTop = im.GetHeight() / 4;
	grx.DrawImage(&im, Gdiplus::RectF(m_bound.left, m_bound.bottom-m_bound.right+m_bound.left, m_bound.right - m_bound.left, m_bound.right - m_bound.left), iLeft, iTop, im.GetWidth() / 4, im.GetHeight() / 4, Gdiplus::UnitPixel);
	//4.滑块
	iTop = im.GetHeight() / 4 * 3;
	int iThumTop = GetThumLeft();
	grx.DrawImage(&im, Gdiplus::RectF(m_bound.left, iThumTop, m_bound.right - m_bound.left, m_bound.right - m_bound.left), iLeft, iTop, m_bound.right - m_bound.left, m_bound.right - m_bound.left, Gdiplus::UnitPixel);
}
void CQUIScrollBar::SetRang(int iRang)
{
	m_iRang = iRang;
}
int CQUIScrollBar::GetRang()
{
	return m_iRang;
}
void CQUIScrollBar::SetPos(int iPos)
{
	m_iScrollPos = iPos;
	if (m_pCallBack)
	{
		TScrollInfo tSInfo;
		tSInfo.iPos = iPos;
		tSInfo.iMaxPos = m_iRang;
		if (m_eBarStyle == E_ScrollBar_HBar)
			m_pCallBack->OnHScrollBar(&tSInfo);
		else
			m_pCallBack->OnVScrollBar(&tSInfo);
	}
	
	    InvalidBounds();
}
int CQUIScrollBar::GetPos()
{
	return m_iScrollPos;
}
LRESULT CQUIScrollBar::OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	__super::OnControlMessage(message, wParam, lParam);
	//滚动条禁用状态，不响应鼠标事件
	if (m_eState == E_ScrollBarState_Disable)
		return S_FALSE;
	switch (message)
	{
		case WM_LBUTTONDOWN:
		{
			 POINT pt;
			 pt.x = LOWORD(lParam);
			 pt.y = HIWORD(lParam);
			 if (HitTest(pt))
			 {
				 m_eState = E_ScrollBarState_Down;
				 RECT rcThum;
				 GetThumRect(rcThum);
				 if (PtInRect(&rcThum, pt))
				 {//鼠标在滑块上按下
					 m_bThumPress=TRUE;
				 }
				 else
				 {
					 int iPos = m_iScrollPos;
					 //先判断是否按下左边按钮
					 RECT rcLeftBtn;
					 GetLeftBtnRect(rcLeftBtn);

					 RECT rcRightBtn;
					 GetRightBtnRect(rcRightBtn);
					 if (PtInRect(&rcLeftBtn, pt))
					 {//点击了左边按钮
						 iPos -= 5;
					 }
					 //判断是否按下右边按钮
					 else if (PtInRect(&rcRightBtn, pt))
					 {//点击了右边按钮
						 iPos += 5;
					 }
					 else
					 {//点击了滚动条空白的背景区域
						 if (m_eBarStyle == E_ScrollBar_HBar)
						 {
							 if (pt.x > rcThum.left)
								 iPos += m_iRang/5;
							 else
								 iPos -= m_iRang / 5;
						 }
						 else
						 {
							 if (pt.y > rcThum.top)
								 iPos += m_iRang / 5;
							 else
								 iPos -= m_iRang / 5;
						 }
					 }
					if (iPos < 0)
						iPos = 0;
					else if (iPos>m_iRang)
						iPos = m_iRang;
					SetPos(iPos);
					return S_OK;
					 
				 }
				 InvalidBounds();
				 return S_OK;
			 }
		}
		break;
		case WM_LBUTTONUP:
		{
		    POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			//if (m_bThumPress)
			{
				if (HitTest(pt))
					m_eState = E_ScrollBarState_Over;
				else
					m_eState = E_ScrollBarState_Normal;
				InvalidBounds();
			}
			m_bThumPress = FALSE;
		}
			break;
		case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			if (m_bThumPress)
			{
				int iPos = 0;
				double dbSub = 0;
				double dbWidth = 0;
				if (m_eBarStyle == E_ScrollBar_HBar)
				{
					dbSub = pt.x - m_bound.left;
					dbWidth = m_bound.right - m_bound.left - (m_bound.bottom - m_bound.top) * 3;
				}
				else
				{
					dbSub = pt.y - m_bound.top;
					dbWidth = m_bound.bottom - m_bound.top - (m_bound.right - m_bound.left) * 3;
				}
				iPos = dbSub / dbWidth*m_iRang;
				if (iPos < 0)
					iPos = 0;
				else if (iPos>m_iRang)
					iPos = m_iRang;
				SetPos(iPos);
				return S_OK;
			}
			if (HitTest(pt))
			{
				m_eState = E_ScrollBarState_Over;
				InvalidBounds();
				return S_OK;
			}
			else
			{
				if (m_eState != E_ScrollBarState_Normal&&m_eState != E_ScrollBarState_Disable)
				{//移出去，状态恢复回去
					m_eState = E_ScrollBarState_Normal;
					InvalidBounds();
					return S_OK;
				}
			}
		}
			break;
	}
	return S_FALSE;
}