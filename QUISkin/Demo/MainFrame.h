#pragma once
#include "QUIWnd.h"
#include"QUIButton.h"
#include"QUIStaticText.h"
#include"QUIEdit.h"
#include"QUIListh.h"
#include"QUITree.h"
#include"QUIScrollBar.h"

class CMainFrame :public CQUIWnd, public IQUIEventCallBack//,public IScrollbarCallback
{
public:
	CMainFrame();
	~CMainFrame();
protected:
	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LPCTSTR GetWndClassName();
	virtual void OnCreate(WPARAM wParam, LPARAM lParam);
	virtual void OnPaint(WPARAM wParam, LPARAM lParam);
	virtual void OnDestoryWindow(WPARAM wParam, LPARAM lParam);
	virtual void OnSize(WPARAM wParam, LPARAM lParam);



	void OnNotifyCmd(CUIElement* pElement);
	

	virtual void OnPaintControl(Gdiplus::Graphics& grx);
private:
	
	CQUIButton m_BtnClose;
	CQUIList   m_List;
};

