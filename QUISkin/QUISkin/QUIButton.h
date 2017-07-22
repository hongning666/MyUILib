#ifndef QUIBUTTON_H_
#define QUIBUTTON_H_
#include"UIElement.h"

enum enButtonState
{
	E_BtnState_Normal = 1,//正常
	E_BtnState_Over=2,//鼠标移上去
	E_BtnState_Down=3,//鼠标按下
	E_BtnState_Disable = 4,//鼠标不可用
	E_BtnState_Focus=5,//获取焦点
};

class QUISKIN_API CQUIButton :public CUIElement
{
public:
	CQUIButton();
	~CQUIButton();
public:
	void SetStateImage(const TCHAR* szImage, int iStateCount = 4);
	/*
	功能：设置按钮状态
	*/
	void SetState(enButtonState eState);
	//判断鼠标点是否在元素区域内
	virtual BOOL HitTest(POINT pt);
protected:
	virtual void DrawStatusImage(Gdiplus::Graphics& grx);

	void OnChangeState();
public:
	virtual LRESULT OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
	enButtonState m_eState;//鼠标状态
	UINT          m_iStateCount;//按钮有几种状态
	StdString     m_strStateImage;//按钮状态图
};




#endif