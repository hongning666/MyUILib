#ifndef _QUIWND_H_
#define _QUIWND_H_
#include"QUISkin.h"
#include<gdiplus.h>

class QUISKIN_API CQUIWnd
{
public:
	CQUIWnd();
	virtual~CQUIWnd();
public:
	HWND Create(HWND hWndParent, LPCTSTR lpszCaption, const RECT rc, DWORD dwStyle, HINSTANCE hInst);
	/*
	功能：设置图标
	参数：
	     @iRes：资源id号
	*/
	void SetIcon(UINT iRes);

	/*
	功能：设置窗口最小大小
	参数：
	     @iWidth：最小宽度
		 @iHeight:最小高度
	*/
	void SetMiniSize(int iWidth, int iHeight);
	/*
	功能:设置窗口区域
	参数:
	    @lpPoint:坐标点列表
		@count:点的数量
	*/
	void SetWindowRgn(POINT* lpPoint, int count);
	/*
	功能:设置鼠标按下拖动窗口的坐标
	*/
	void SetDragRect(const RECT& rc);

	void ShowWindow(UINT nCmd);
	void UpdateWindow();
	/*
	功能：改变窗口坐标
	*/
	void MoveWindow(const RECT& rc,BOOL bRepaint);
	/*
	功能：允许/禁止窗口接受鼠标和键盘输入
	参数:
	     @bEnable:TRUE 是允许,FLASE是禁止
	*/
	void EnableWindow(BOOL bEnable);
	/*
	功能:设置背景图
	*/
	void SetBground(const StdString& strFile);
	/*
	功能:获取窗口客户区坐标
	*/
	BOOL GetClientRect(RECT* rc);
	/*
	功能:获取窗口坐标
	*/
	BOOL GetWindowRect(RECT* rc);
protected:
	//注册窗口
	virtual BOOL RegisterWndClass();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);
	//获取窗口名字
	virtual LPCTSTR GetWndClassName();
	//消息处理函数
	virtual LRESULT HandleMessage(UINT message, WPARAM wparam, LPARAM lparam);
protected:
	virtual void OnPaint(WPARAM wparam, LPARAM lparam);
	virtual void OnSize(WPARAM wparam,LPARAM lparam);
	virtual void OnCreate(WPARAM wparam, LPARAM lparam);
	virtual void OnLButtonDown(WPARAM wparam, LPARAM lparam);
	virtual void OnLButtonUp(WPARAM wparam, LPARAM lparam);
	virtual void OnMouseMove(WPARAM wparam, LPARAM lparam);
	virtual void OnClose(WPARAM wparam, LPARAM lparam);
	virtual void OnDestoryWindow(WPARAM wparam, LPARAM lparam);
	virtual void OnActivate(WPARAM wparam, LPARAM lparam);
	virtual void OnKillFocus(WPARAM wparam, LPARAM lparam);
	virtual void OnSetFocus(WPARAM wparam, LPARAM lparam);
	virtual void OnShowWindow(WPARAM wparam, LPARAM lparam);
	virtual void OnKeyDown(WPARAM wparam, LPARAM lparam);
	virtual HBRUSH OnCtrlColorEdit(WPARAM wparam, LPARAM lparam);
protected:
	/*
	功能:元素的绘制
	*/
	virtual void OnPaintControl(Gdiplus::Graphics& grx);
protected:
	HWND m_hWnd;
	HINSTANCE m_hInst;

	int m_iMinWidth;//窗口最小宽度
	int m_iMinHeight;//窗口最小高度

	HRGN m_hRgn;//窗口区域

	RECT m_tDragRc;//鼠标按下拖动窗口的区域

	BOOL m_bDrag;//是否处理窗口拖动状态

	POINT m_tPt;//鼠标按下的坐标点

	StdString m_szBground;//窗口背景位图

};


#endif