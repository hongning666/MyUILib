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
	InvalidBounds();//����Ч����
}
void CQUIButton::DrawStatusImage(Gdiplus::Graphics& grx)
{
	if (m_strStateImage.length() <= 0)
		return;
	//1.����ͼƬ
	Gdiplus::Image im(m_strStateImage.c_str());
	//2.����ͼƬ�ȷ�
	int iLeft = im.GetWidth() / m_iStateCount*(m_eState - 1);
	//3.��ͼ��״̬ͼ
	//��ť���������������ϵ�����
	Gdiplus::RectF destRc(m_bound.left, m_bound.top, m_bound.right - m_bound.left, m_bound.bottom - m_bound.top);
	//��ͼ
	grx.DrawImage(&im, destRc,iLeft, 0, im.GetWidth() / m_iStateCount, im.GetHeight(), Gdiplus::UnitPixel);
}

LRESULT CQUIButton::OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	__super::OnControlMessage(message, wParam, lParam);
	switch (message)
	{
	case WM_MOUSEMOVE:
		{//����ڰ�ť�ϻ���(over״̬)
			POINT pt;
			pt.x = LOWORD(lParam);//���ֽڱ�������x����
			pt.y = HIWORD(lParam);//���ֽڱ�������y����
			if (HitTest(pt))
			{//�ж�����Ƿ��ڰ�ť����

				if (m_eState != E_BtnState_Over)
				{//����Ѿ���over״̬����ô�������ػ�״̬�����ٻ��ƿ���
					SetState(E_BtnState_Over);
				}
				return S_OK;
			}
			else
			{//��겻�����ǰ�ť���򣬻ָ���ť״̬

				if (m_eState != E_BtnState_Normal)
				{//�ж��������Ƿ����ϴεĵ�ǰ��ť
					SetState(E_BtnState_Normal);
				}
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{//��갴��
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
		{//���̧��
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			if (HitTest(pt))
			{
				if (m_pCallBack)
					m_pCallBack->OnNotifyCmd(this);//��Ӧ������¼�

				//���ð�ť״̬
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