#include"stdafx.h"
#include"QUIButton.h"

CQUIButton::CQUIButton()
{
	m_iStateCount = 4;
	m_eState = E_BtnState_Normal;
}

CQUIButton::~CQUIButton()
{

}
void CQUIButton::SetStateImage(const TCHAR* szImage, int iStateCount)
{
	if (szImage)
	{
		m_strStateImage = szImage;
		m_iStateCount = iStateCount;
	}
}
void CQUIButton::SetState(enButtonState eState)
{
	m_eState = eState;
	OnChangeState();
}

void CQUIButton::OnChangeState()
{
	InvalidBounds();//置无效区域
}
void CQUIButton::DrawStatusImage(Gdiplus::Graphics& grx)
{
	if (m_strStateImage.length() <= 0)
		return;
	//1.加载图片
	Gdiplus::Image im(m_strStateImage.c_str());
	//2.进行图片等分
	int iLeft = im.GetWidth() / m_iStateCount*(m_eState - 1);
	//3.切图画状态图
	//按钮本身在宿主窗口上的坐标
	Gdiplus::RectF destRc(m_bound.left, m_bound.top, m_bound.right - m_bound.left, m_bound.bottom - m_bound.top);
	//绘图
	grx.DrawImage(&im, destRc,iLeft, 0, im.GetWidth() / m_iStateCount, im.GetHeight(), Gdiplus::UnitPixel);
}

LRESULT CQUIButton::OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	__super::OnControlMessage(message, wParam, lParam);
	switch (message)
	{
	case WM_MOUSEMOVE:
		{//鼠标在按钮上划过(over状态)
			POINT pt;
			pt.x = LOWORD(lParam);//低字节保存鼠标的x坐标
			pt.y = HIWORD(lParam);//高字节保存鼠标的y坐标
			if (HitTest(pt))
			{//判断鼠标是否在按钮上面

				if (m_eState != E_BtnState_Over)
				{//如果已经是over状态，那么无需再重绘状态，减少绘制开销
					SetState(E_BtnState_Over);
				}
				return S_OK;
			}
			else
			{//鼠标不在我们按钮区域，恢复按钮状态

				if (m_eState != E_BtnState_Normal)
				{//判断这个鼠标是否是上次的当前按钮
					SetState(E_BtnState_Normal);
				}
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{//鼠标按下
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			if (HitTest(pt))
			{
				SetState(E_BtnState_Down);
				return S_OK;
			}
		}
		break;
	case WM_LBUTTONUP:
		{//鼠标抬起
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			if (HitTest(pt))
			{
				if (m_pCallBack)
					m_pCallBack->OnNotifyCmd(this);//响应鼠标点击事件

				//重置按钮状态
				SetState(E_BtnState_Normal);
				return S_OK;
			}
		}
		break;
	}
	return S_FALSE;
}
BOOL CQUIButton::HitTest(POINT pt)
{
	if (IsVisible())
		return __super::HitTest(pt);

	return FALSE;
}