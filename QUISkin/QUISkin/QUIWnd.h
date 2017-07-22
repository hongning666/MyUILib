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
	���ܣ�����ͼ��
	������
	     @iRes����Դid��
	*/
	void SetIcon(UINT iRes);

	/*
	���ܣ����ô�����С��С
	������
	     @iWidth����С���
		 @iHeight:��С�߶�
	*/
	void SetMiniSize(int iWidth, int iHeight);
	/*
	����:���ô�������
	����:
	    @lpPoint:������б�
		@count:�������
	*/
	void SetWindowRgn(POINT* lpPoint, int count);
	/*
	����:������갴���϶����ڵ�����
	*/
	void SetDragRect(const RECT& rc);

	void ShowWindow(UINT nCmd);
	void UpdateWindow();
	/*
	���ܣ��ı䴰������
	*/
	void MoveWindow(const RECT& rc,BOOL bRepaint);
	/*
	���ܣ�����/��ֹ���ڽ������ͼ�������
	����:
	     @bEnable:TRUE ������,FLASE�ǽ�ֹ
	*/
	void EnableWindow(BOOL bEnable);
	/*
	����:���ñ���ͼ
	*/
	void SetBground(const StdString& strFile);
	/*
	����:��ȡ���ڿͻ�������
	*/
	BOOL GetClientRect(RECT* rc);
	/*
	����:��ȡ��������
	*/
	BOOL GetWindowRect(RECT* rc);
protected:
	//ע�ᴰ��
	virtual BOOL RegisterWndClass();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);
	//��ȡ��������
	virtual LPCTSTR GetWndClassName();
	//��Ϣ������
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
	����:Ԫ�صĻ���
	*/
	virtual void OnPaintControl(Gdiplus::Graphics& grx);
protected:
	HWND m_hWnd;
	HINSTANCE m_hInst;

	int m_iMinWidth;//������С���
	int m_iMinHeight;//������С�߶�

	HRGN m_hRgn;//��������

	RECT m_tDragRc;//��갴���϶����ڵ�����

	BOOL m_bDrag;//�Ƿ������϶�״̬

	POINT m_tPt;//��갴�µ������

	StdString m_szBground;//���ڱ���λͼ

};


#endif