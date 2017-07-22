#ifndef QUIBUTTON_H_
#define QUIBUTTON_H_
#include"UIElement.h"

enum enButtonState
{
	E_BtnState_Normal = 1,//����
	E_BtnState_Over=2,//�������ȥ
	E_BtnState_Down=3,//��갴��
	E_BtnState_Disable = 4,//��겻����
	E_BtnState_Focus=5,//��ȡ����
};

class QUISKIN_API CQUIButton :public CUIElement
{
public:
	CQUIButton();
	~CQUIButton();
public:
	void SetStateImage(const TCHAR* szImage, int iStateCount = 4);
	/*
	���ܣ����ð�ť״̬
	*/
	void SetState(enButtonState eState);
	//�ж������Ƿ���Ԫ��������
	virtual BOOL HitTest(POINT pt);
protected:
	virtual void DrawStatusImage(Gdiplus::Graphics& grx);

	void OnChangeState();
public:
	virtual LRESULT OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
	enButtonState m_eState;//���״̬
	UINT          m_iStateCount;//��ť�м���״̬
	StdString     m_strStateImage;//��ť״̬ͼ
};




#endif