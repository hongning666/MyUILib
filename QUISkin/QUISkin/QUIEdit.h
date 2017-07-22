#ifndef QUIEDIT_H_
#define QUIEDIT_H_
#include"UIElement.h"
#include"QUIWnd.h"


enum enEditState
{
	E_EditState_Normal = 1,
	E_EditState_Over=2,
	E_EditState__Focus=3,
};

class QUISKIN_API CQUIEdit :public CUIElement,public CQUIWnd
{//利用CUIElement来绘制边框
public:
	CQUIEdit();
	~CQUIEdit();
public:
	void SetStyle(DWORD dwStyle);
	BOOL Create(const TCHAR* szEleID, const RECT& rc, HWND hWndParent, HINSTANCE hInst, IQUIEventCallBack* pCallBack = NULL);
public:
	void SetState(enEditState eState);
	void SetLightColor(DWORD dwLightColor1, DWORD dwLightColor2);
	virtual LRESULT OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	virtual void DrawBorder(Gdiplus::Graphics& grx);

	static LRESULT CALLBACK OnControlProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleMessage(UINT message, WPARAM wparam, LPARAM lparam);
	
	virtual LPCTSTR GetWndClassName();
	virtual BOOL RegisterWndClass();
protected:
	enEditState m_eState;
	DWORD       m_dwLightColor1;//over
	DWORD       m_dwLightColor2;//Focus
	DWORD       m_dwStyle;

	WNDPROC     m_pOldWndProc;
};












#endif